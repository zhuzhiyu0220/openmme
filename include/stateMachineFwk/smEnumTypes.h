/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright 2019-present, Infosys Limited.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef SM_ENUMS_H
#define SM_ENUMS_H
/**************************************
 * 
 * This is an auto generated file.
 * Please do not edit this file.
 * All edits to be made through template source file
 * <TOP-DIR/scripts/SMCodeGen/templates/stateMachineTmpls/enum.tt>
 **************************************/
 
enum State_e
{ 
    attach_start, 
    attach_wf_aia, 
    attach_wf_att_cmp, 
    attach_wf_auth_resp, 
    attach_wf_auth_resp_validate, 
    attach_wf_cs_resp, 
    attach_wf_esm_info_check, 
    attach_wf_esm_info_resp, 
    attach_wf_identity_response, 
    attach_wf_imsi_validate_action, 
    attach_wf_init_ctxt_resp, 
    attach_wf_init_ctxt_resp_att_cmp, 
    attach_wf_mb_resp, 
    attach_wf_sec_cmp, 
    attach_wf_ula, 
    default_mme_state, 
    detach_start, 
    detach_wf_del_session_resp, 
    ni_detach_start, 
    ni_detach_wf_del_sess_resp, 
    ni_detach_wf_det_accpt_del_sess_resp, 
    ni_detach_wf_detach_accept, 
    ni_detach_wf_s1_rel_comp, 
    paging_start, 
    paging_wf_service_req, 
    s1_release_start, 
    s1_release_wf_release_access_bearer_resp, 
    s1_release_wf_ue_ctxt_release_comp, 
    service_request_start, 
    service_request_wf_aia, 
    service_request_wf_auth_resp_validate, 
    service_request_wf_auth_response, 
    service_request_wf_init_ctxt_resp, 
    service_request_wf_mb_resp, 
    service_request_wf_sec_cmp, 
    tau_start, 
    tau_wf_aia, 
    tau_wf_auth_resp_validate, 
    tau_wf_auth_response, 
    tau_wf_sec_cmp,
    END_STATE
};

static constexpr const char* States[] =
{
    "attach_start",
    "attach_wf_aia",
    "attach_wf_att_cmp",
    "attach_wf_auth_resp",
    "attach_wf_auth_resp_validate",
    "attach_wf_cs_resp",
    "attach_wf_esm_info_check",
    "attach_wf_esm_info_resp",
    "attach_wf_identity_response",
    "attach_wf_imsi_validate_action",
    "attach_wf_init_ctxt_resp",
    "attach_wf_init_ctxt_resp_att_cmp",
    "attach_wf_mb_resp",
    "attach_wf_sec_cmp",
    "attach_wf_ula",
    "default_mme_state",
    "detach_start",
    "detach_wf_del_session_resp",
    "ni_detach_start",
    "ni_detach_wf_del_sess_resp",
    "ni_detach_wf_det_accpt_del_sess_resp",
    "ni_detach_wf_detach_accept",
    "ni_detach_wf_s1_rel_comp",
    "paging_start",
    "paging_wf_service_req",
    "s1_release_start",
    "s1_release_wf_release_access_bearer_resp",
    "s1_release_wf_ue_ctxt_release_comp",
    "service_request_start",
    "service_request_wf_aia",
    "service_request_wf_auth_resp_validate",
    "service_request_wf_auth_response",
    "service_request_wf_init_ctxt_resp",
    "service_request_wf_mb_resp",
    "service_request_wf_sec_cmp",
    "tau_start",
    "tau_wf_aia",
    "tau_wf_auth_resp_validate",
    "tau_wf_auth_response",
    "tau_wf_sec_cmp",
    "END_STATE"
};

enum Event_e
{
    ABORT_EVENT,
    AIA_FROM_HSS,
    ATT_CMP_FROM_UE,
    ATTACH_REQ_FROM_UE,
    AUTH_RESP_FAILURE,
    AUTH_RESP_FROM_UE,
    AUTH_RESP_SUCCESS,
    AUTH_RESP_SYNC_FAILURE,
    CLR_FROM_HSS,
    CS_RESP_FROM_SGW,
    DDN_FROM_SGW,
    DEL_SESSION_RESP_FROM_SGW,
    DETACH_ACCEPT_FROM_UE,
    DETACH_REQ_FROM_UE,
    ESM_INFO_NOT_REQUIRED,
    ESM_INFO_REQUIRED,
    ESM_INFO_RESP_FROM_UE,
    IDENTITY_RESPONSE_FROM_UE,
    IMSI_VALIDATION_FAILURE,
    IMSI_VALIDATION_SUCCESS,
    INIT_CTXT_RESP_FROM_UE,
    MB_RESP_FROM_SGW,
    REL_AB_RESP_FROM_SGW,
    S1_REL_REQ_FROM_UE,
    SEC_MODE_RESP_FROM_UE,
    SERVICE_REQUEST_FROM_UE,
    TAU_REQUEST_FROM_UE,
    UE_CTXT_REL_COMP_FROM_ENB,
    ULA_FROM_HSS,
    VALIDATE_IMSI,
    END_EVENT
};

static constexpr const char* Events[] =
{
    "ABORT_EVENT",
    "AIA_FROM_HSS",
    "ATT_CMP_FROM_UE",
    "ATTACH_REQ_FROM_UE",
    "AUTH_RESP_FAILURE",
    "AUTH_RESP_FROM_UE",
    "AUTH_RESP_SUCCESS",
    "AUTH_RESP_SYNC_FAILURE",
    "CLR_FROM_HSS",
    "CS_RESP_FROM_SGW",
    "DDN_FROM_SGW",
    "DEL_SESSION_RESP_FROM_SGW",
    "DETACH_ACCEPT_FROM_UE",
    "DETACH_REQ_FROM_UE",
    "ESM_INFO_NOT_REQUIRED",
    "ESM_INFO_REQUIRED",
    "ESM_INFO_RESP_FROM_UE",
    "IDENTITY_RESPONSE_FROM_UE",
    "IMSI_VALIDATION_FAILURE",
    "IMSI_VALIDATION_SUCCESS",
    "INIT_CTXT_RESP_FROM_UE",
    "MB_RESP_FROM_SGW",
    "REL_AB_RESP_FROM_SGW",
    "S1_REL_REQ_FROM_UE",
    "SEC_MODE_RESP_FROM_UE",
    "SERVICE_REQUEST_FROM_UE",
    "TAU_REQUEST_FROM_UE",
    "UE_CTXT_REL_COMP_FROM_ENB",
    "ULA_FROM_HSS",
    "VALIDATE_IMSI",
    "END_EVENT"
};

enum Action_e
{
    ABORT_ATTACH,
    ABORT_SERVICE_REQ_PROCEDURE,
    ABORT_TAU_PROCEDURE,
    ATTACH_DONE,
    AUTH_REQ_TO_UE,
    AUTH_RESPONSE_VALIDATE,
    CHECK_ESM_INFO_REQ_REQUIRED,
    CS_REQ_TO_SGW,
    DEFAULT_ATTACH_REQ_HANDLER,
    DEFAULT_CANCEL_LOC_REQ_HANDLER,
    DEFAULT_DDN_HANDLER,
    DEFAULT_DETACH_REQ_HANDLER,
    DEFAULT_S1_RELEASE_REQ_HANDLER,
    DEFAULT_SERVICE_REQ_HANDLER,
    DEFAULT_TAU_REQ_HANDLER,
    DEL_SESSION_REQ,
    DETACH_ACCEPT_TO_UE,
    NI_DETACH_REQ_TO_UE,
    PROCESS_AIA,
    PROCESS_ATTACH_CMP_FROM_UE,
    PROCESS_CS_RESP,
    PROCESS_DEL_SESSION_RESP,
    PROCESS_DETACH_ACCEPT_FROM_UE,
    PROCESS_ESM_INFO_RESP,
    PROCESS_IDENTITY_RESPONSE,
    PROCESS_INIT_CTXT_RESP,
    PROCESS_INIT_CTXT_RESP_SVC_REQ,
    PROCESS_MB_RESP,
    PROCESS_MB_RESP_SVC_REQ,
    PROCESS_REL_AB_RESP_FROM_SGW,
    PROCESS_SEC_MODE_RESP,
    PROCESS_SERVICE_REQUEST,
    PROCESS_UE_CTXT_REL_COMP,
    PROCESS_UE_CTXT_REL_COMP_FOR_DETACH,
    PROCESS_ULA,
    SEC_MODE_CMD_TO_UE,
    SEND_AIR_TO_HSS,
    SEND_ATTACH_REJECT,
    SEND_AUTH_REJECT,
    SEND_DDN_ACK_TO_SGW,
    SEND_ESM_INFO_REQ_TO_UE,
    SEND_IDENTITY_REQUEST_TO_UE,
    SEND_INIT_CTXT_REQ_TO_UE,
    SEND_INIT_CTXT_REQ_TO_UE_SVC_REQ,
    SEND_MB_REQ_TO_SGW,
    SEND_MB_REQ_TO_SGW_SVC_REQ,
    SEND_PAGING_REQ_TO_UE,
    SEND_REL_AB_REQ_TO_SGW,
    SEND_S1_REL_CMD_TO_UE,
    SEND_S1_REL_CMD_TO_UE_FOR_DETACH,
    SEND_SERVICE_REJECT,
    SEND_TAU_REJECT,
    SEND_TAU_RESPONSE_TO_UE,
    SEND_ULR_TO_HSS,
    VALIDATE_IMSI_IN_UE_CONTEXT,
    END_ACTION
};

static constexpr const char* Actions[] =
{
    "ABORT_ATTACH",
    "ABORT_SERVICE_REQ_PROCEDURE",
    "ABORT_TAU_PROCEDURE",
    "ATTACH_DONE",
    "AUTH_REQ_TO_UE",
    "AUTH_RESPONSE_VALIDATE",
    "CHECK_ESM_INFO_REQ_REQUIRED",
    "CS_REQ_TO_SGW",
    "DEFAULT_ATTACH_REQ_HANDLER",
    "DEFAULT_CANCEL_LOC_REQ_HANDLER",
    "DEFAULT_DDN_HANDLER",
    "DEFAULT_DETACH_REQ_HANDLER",
    "DEFAULT_S1_RELEASE_REQ_HANDLER",
    "DEFAULT_SERVICE_REQ_HANDLER",
    "DEFAULT_TAU_REQ_HANDLER",
    "DEL_SESSION_REQ",
    "DETACH_ACCEPT_TO_UE",
    "NI_DETACH_REQ_TO_UE",
    "PROCESS_AIA",
    "PROCESS_ATTACH_CMP_FROM_UE",
    "PROCESS_CS_RESP",
    "PROCESS_DEL_SESSION_RESP",
    "PROCESS_DETACH_ACCEPT_FROM_UE",
    "PROCESS_ESM_INFO_RESP",
    "PROCESS_IDENTITY_RESPONSE",
    "PROCESS_INIT_CTXT_RESP",
    "PROCESS_INIT_CTXT_RESP_SVC_REQ",
    "PROCESS_MB_RESP",
    "PROCESS_MB_RESP_SVC_REQ",
    "PROCESS_REL_AB_RESP_FROM_SGW",
    "PROCESS_SEC_MODE_RESP",
    "PROCESS_SERVICE_REQUEST",
    "PROCESS_UE_CTXT_REL_COMP",
    "PROCESS_UE_CTXT_REL_COMP_FOR_DETACH",
    "PROCESS_ULA",
    "SEC_MODE_CMD_TO_UE",
    "SEND_AIR_TO_HSS",
    "SEND_ATTACH_REJECT",
    "SEND_AUTH_REJECT",
    "SEND_DDN_ACK_TO_SGW",
    "SEND_ESM_INFO_REQ_TO_UE",
    "SEND_IDENTITY_REQUEST_TO_UE",
    "SEND_INIT_CTXT_REQ_TO_UE",
    "SEND_INIT_CTXT_REQ_TO_UE_SVC_REQ",
    "SEND_MB_REQ_TO_SGW",
    "SEND_MB_REQ_TO_SGW_SVC_REQ",
    "SEND_PAGING_REQ_TO_UE",
    "SEND_REL_AB_REQ_TO_SGW",
    "SEND_S1_REL_CMD_TO_UE",
    "SEND_S1_REL_CMD_TO_UE_FOR_DETACH",
    "SEND_SERVICE_REJECT",
    "SEND_TAU_REJECT",
    "SEND_TAU_RESPONSE_TO_UE",
    "SEND_ULR_TO_HSS",
    "VALIDATE_IMSI_IN_UE_CONTEXT",
    "END_ACTION"
};

#endif
