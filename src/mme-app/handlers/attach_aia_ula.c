/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>


#include "mme_app.h"
#include "ue_table.h"
#include "err_codes.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "stage1_s6a_msg.h"
#include "stage2_info.h"
#include "sec.h"
#include "common_proc_info.h"

/************************************************************************
Current file : Stage 2 handler.
ATTACH stages :
	Stage 1 : IAM-->[stage1 handler]-->AIR, ULR
-->	Stage 2 : AIA, ULA -->[stage2 handler]--> Auth req
	Stage 3 : Auth resp-->[stage3 handler]-->Sec mode cmd
	Stage 4 : sec mode resp-->[stage4 handler]-->esm infor req
	Stage 5 : esm infor resp-->[stage5 handler]-->create session
	Stage 6 : create session resp-->[stage6 handler]-->init ctx setup
	Stage 7 : attach complete-->[stage7 handler]-->modify bearer
**************************************************************************/

/****Globals and externs ***/

extern struct UE_info * g_UE_list[];
extern int g_mme_hdlr_status;

static int g_Q_aia_fd;
static int g_Q_ula_fd;
static int g_Q_authreq_fd;
extern int g_Q_s1ap_common_reject;
extern pthread_mutex_t s1ap_reject_queue_mutex;
extern uint32_t attach_reject_counter;

/*Making global just to avoid stack passing*/
static char aia[S6A_AIA_STAGE2_BUF_SIZE];
static char ula[S6A_ULA_STAGE2_BUF_SIZE];
static fd_set s6a_fds;

extern uint32_t attach_stage2_counter;
/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	if ((g_Q_aia_fd  = open_ipc_channel(S6A_AIA_STAGE2_QUEUE, IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening reader staage 1 IPC channel.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage 2 reader  - AIA : Connected\n");

	if ((g_Q_ula_fd  = open_ipc_channel(S6A_ULA_STAGE2_QUEUE, IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening reader staage 1 IPC channel.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage 2 reader  - ULA : Connected\n");

	/*Open destination queue for writing. */
	log_msg(LOG_INFO, "Stage 2 witer  - s1ap Auth request: waiting\n");
	g_Q_authreq_fd = open_ipc_channel(S1AP_AUTHREQ_STAGE2_QUEUE, IPC_WRITE);

	if (g_Q_authreq_fd == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel: s1ap Auth req\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage2 writer - s1ap Auth request: Connected\n");
	return;
}

static int
process_aia_resp()
{
	struct aia_Q_msg *aia_msg = (struct aia_Q_msg *)aia;
	struct UE_info *ue_entry = GET_UE_ENTRY(aia_msg->ue_idx);;
    if((ue_entry == NULL) || (!IS_VALID_UE_INFO(ue_entry)))
    {
        log_msg(LOG_INFO, "process_aia_resp for bad UE at index %d ", aia_msg->ue_idx);
        return E_FAIL;
    }

	log_msg(LOG_INFO, "AIA for UE idx = %d\n", aia_msg->ue_idx);
	if(NULL == ue_entry->aia_sec_info) {
		ue_entry->aia_sec_info = calloc(sizeof(struct E_UTRAN_sec_vector), 1);
		if(NULL == ue_entry->aia_sec_info) {
			fprintf(stderr, "alloca failed\n");
			exit(0);
		}
	}

    if(S6A_AIA_FAILED == aia_msg->res)
    {
        /* send attach reject and release UE */
		ue_entry->ue_state = STAGE1_AIA_FAIL;
        return aia_msg->ue_idx;
    }

	memcpy(ue_entry->aia_sec_info,
		&(aia_msg->sec),
		sizeof(struct E_UTRAN_sec_vector));

	/*If ula also done then set flag for next stage*/
	if((STAGE1_ULA_DONE == ue_entry->ue_state) || (ATTACH_STAGE1_RESYNC ==  ue_entry->ue_state)) {
		ue_entry->ue_state = ATTACH_STAGE2;
		attach_stage2_counter++;
	}
	else
		ue_entry->ue_state = STAGE1_AIA_DONE;

	return aia_msg->ue_idx;
}

static int
process_ula_resp()
{
	struct ula_Q_msg *ula_msg = (struct ula_Q_msg *)ula;
	struct UE_info *ue_entry = GET_UE_ENTRY(ula_msg->ue_idx);;
    if((ue_entry == NULL) || (!IS_VALID_UE_INFO(ue_entry)))
    {
        log_msg(LOG_INFO, "process_ula_resp for bad UE at index %d ", ula_msg->ue_idx);
        return E_FAIL;
    }

	log_msg(LOG_INFO, "ULA for UE idx = %d\n", ula_msg->ue_idx);

	memcpy(ue_entry->MSISDN, ula_msg->MSISDN, MSISDN_STR_LEN);
	ue_entry->apn_config_profile_ctx_id = ula_msg->apn_config_profile_ctx_id;
	ue_entry->RAU_TAU_timer = ula_msg->RAU_TAU_timer;
	ue_entry->subscription_status = ula_msg->subscription_status;
	ue_entry->net_access_mode = ula_msg->net_access_mode;
	ue_entry->access_restriction_data = ula_msg->access_restriction_data;
	ue_entry->ambr.max_requested_bw_dl = ula_msg->max_requested_bw_dl;
	ue_entry->ambr.max_requested_bw_ul = ula_msg->max_requested_bw_ul;
	ue_entry->pdn_addr.pdn_type =  1;
	ue_entry->pdn_addr.ip_type.ipv4.s_addr = ntohl(ula_msg->static_addr); // network byte order 
	log_msg(LOG_INFO, "PAA address - %s\n", inet_ntoa(ue_entry->pdn_addr.ip_type.ipv4));

	ue_entry->selected_apn.len = ula_msg->selected_apn.len;
	log_msg(LOG_INFO, "APN length from ula msg is - %d\n",
			ula_msg->selected_apn.len);
	memcpy(ue_entry->selected_apn.val, ula_msg->selected_apn.val,
			ula_msg->selected_apn.len);
	log_msg(LOG_INFO, "APN name from ula msg is - %s\n",
			ula_msg->selected_apn.val);

	ue_entry->selected_apn.len = ula_msg->selected_apn.len;
	memcpy(ue_entry->selected_apn.val, ula_msg->selected_apn.val,
			ula_msg->selected_apn.len);
	log_msg(LOG_INFO, "APN name and length from ula msg is - %s-%d\n",
			ula_msg->selected_apn.val, ula_msg->selected_apn.len);

	if(STAGE1_AIA_DONE == ue_entry->ue_state) {
		ue_entry->ue_state = ATTACH_STAGE2;
		attach_stage2_counter++;
	}
	else
		ue_entry->ue_state = STAGE1_ULA_DONE;

	return ula_msg->ue_idx;
}


/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;
	struct timeval t;
	t.tv_sec = 0;
	t.tv_usec = 500;
	int ret = 0;

	/*Need to listen on two FD. using select*/
	FD_ZERO(&s6a_fds);
	FD_SET(g_Q_ula_fd, &s6a_fds);
	FD_SET(g_Q_aia_fd, &s6a_fds);

	memset(aia, 0, S6A_AIA_STAGE2_BUF_SIZE);

	ret = select(g_Q_ula_fd+1, &s6a_fds, NULL, NULL, &t);
	 switch (ret) {
		case -1:
		perror("select()");
		log_msg(LOG_ERROR, "Select failed for AIA and ULA\n");
		return -1;

		case 0:
		//log_msg(LOG_ERROR, "Select failed for AIA and ULA - 0\n");
		return -1;

		default:
		/* All fd_set's should be checked. */
		if (FD_ISSET(g_Q_aia_fd, &s6a_fds)) {
			while (bytes_read < S6A_AIA_STAGE2_BUF_SIZE) {//TODO : Recheck condition
			if ((bytes_read = read_ipc_channel(
				g_Q_aia_fd, aia, S6A_AIA_STAGE2_BUF_SIZE)) == -1) {
				log_msg(LOG_ERROR, "Error in reading \n");
				/* TODO : Add proper error handling */
			}
			log_msg(LOG_INFO, "AIA Message Received - Len: %d\n",bytes_read);
			return process_aia_resp();
			}
		} else if (FD_ISSET(g_Q_ula_fd, &s6a_fds)) {
			while (bytes_read < S6A_ULA_STAGE2_BUF_SIZE) {//TODO : Recheck condition
			if ((bytes_read = read_ipc_channel(
				g_Q_ula_fd, ula, S6A_ULA_STAGE2_BUF_SIZE)) == -1) {
				log_msg(LOG_ERROR, "Error in reading \n");
				/* TODO : Add proper error handling */
			}
			log_msg(LOG_INFO, "ULA Message Received - Len: %d\n",bytes_read);
			}
			return process_ula_resp();
		}
		}

#if 0
	while (bytes_read < S6A_AIA_STAGE2_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
			g_Q_aia_fd, aia, S6A_AIA_STAGE2_BUF_SIZE)) == -1) {
			log_msg(LOG_ERROR, "Error in reading \n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, "AIA Message Received - Len: %d\n",bytes_read);
	}
#endif
	return ret;
}

/**
* Stage specific message processing.
*/
static int
stage2_processing()
{
	/*Parse and validate  the buffer*/
	/*Find the UE*/
	/*Check the state*/
	/*Collect information for next processing*/
	/*post to next processing*/
	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next(int ue_index)
{
	struct UE_info *ue_entry = GET_UE_ENTRY(ue_index);

    if((ue_entry == NULL) || (!IS_VALID_UE_INFO(ue_entry)))
    {
        log_msg(LOG_INFO, "post_to_next for bad UE at index %d ", ue_index);
        return E_FAIL;
    }

	if(ue_entry->ue_state == ATTACH_STAGE2) {

		/* Create integrity key */
		create_integrity_key(ue_entry->aia_sec_info->kasme.val,
				ue_entry->ue_sec_info.int_key);

		ue_entry->dl_seq_no = 0;

		log_msg(LOG_INFO, "Attach stage2 started. %d\n", ue_index);


		/*Create message to send to S1ap*/
		struct authreq_info authreq;
		authreq.enb_fd = ue_entry->enb_fd;
		authreq.ue_idx = ue_index;
		authreq.enb_s1ap_ue_id = ue_entry->s1ap_enb_ue_id;
		memcpy(&(authreq.rand), &(ue_entry->aia_sec_info->rand.val),
				NAS_RAND_SIZE);
		memcpy(&(authreq.autn), &(ue_entry->aia_sec_info->autn.val),
				NAS_AUTN_SIZE);

		/*post message to next stage i.e. s1ap auth req*/
		write_ipc_channel(g_Q_authreq_fd, (char *)&(authreq),
				S1AP_AUTHREQ_STAGE2_BUF_SIZE);
		log_msg(LOG_INFO, "Stage 2. Posted message to s1ap - Auth req\n");

		/*TODO free g_UE_list[][].aia_sec_info??*/
	}
    else if (STAGE1_AIA_FAIL == ue_entry->ue_state)
    {
        char imsiStr[16] = {0};
        imsi_bin_to_str(ue_entry->IMSI, imsiStr);
        log_msg(LOG_ERROR, "Error AIA from HSS. Send Attach Reject & \
                Release UE session. UE IMSI: %s. \n", imsiStr);
   	    struct s1ap_common_req_Q_msg s1ap_rej = {0};
        s1ap_rej.IE_type = S1AP_ATTACH_REJ;
        s1ap_rej.ue_idx = ue_index;
        s1ap_rej.mme_s1ap_ue_id = ue_index;
        s1ap_rej.enb_s1ap_ue_id = ue_entry->s1ap_enb_ue_id;
        s1ap_rej.enb_fd = ue_entry->enb_fd;
        s1ap_rej.cause.present = s1apCause_PR_misc;
        s1ap_rej.cause.choice.misc = s1apCauseMisc_unknown_PLMN;
		
        pthread_mutex_lock(&s1ap_reject_queue_mutex);
        write_ipc_channel(g_Q_s1ap_common_reject, 
                          (char *)&(s1ap_rej),
				          S1AP_COMMON_REQ_BUF_SIZE);
        pthread_mutex_unlock(&s1ap_reject_queue_mutex);
        release_ue_entry(ue_entry); 
    }
	
    return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_stage2()
{
	close_ipc_channel(g_Q_aia_fd);
	close_ipc_channel(g_Q_ula_fd);
	close_ipc_channel(g_Q_authreq_fd);
	log_msg(LOG_INFO, "Shutdown Stage 2 handler \n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
stage2_handler(void *data)
{
	int ue_index = -1;
	init_stage();
	log_msg(LOG_INFO, "Stage 2 ready.\n");
	g_mme_hdlr_status <<= 1;
	g_mme_hdlr_status |= 1;
	check_mme_hdlr_status();

	while(1){
		ue_index = read_next_msg();

		stage2_processing();

		if (ue_index >= 0)
			post_to_next(ue_index);
	}

	return NULL;
}
