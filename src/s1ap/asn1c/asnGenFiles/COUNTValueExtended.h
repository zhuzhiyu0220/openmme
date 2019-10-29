/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "S1AP-IEs"
 * 	found in "./asn1c/S1AP-IEs.asn"
 * 	`asn1c -fcompound-names -fno-include-deps -gen-PER -findirect-choice -pdu=S1AP-PDU`
 */

#ifndef	_COUNTValueExtended_H_
#define	_COUNTValueExtended_H_


#include <asn_application.h>

/* Including external dependencies */
#include "PDCP-SNExtended.h"
#include "HFNModified.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct ProtocolExtensionContainer;

/* COUNTValueExtended */
typedef struct COUNTValueExtended {
	PDCP_SNExtended_t	 pDCP_SNExtended;
	HFNModified_t	 hFNModified;
	struct ProtocolExtensionContainer	*iE_Extensions;	/* OPTIONAL */
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} COUNTValueExtended_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_COUNTValueExtended;
extern asn_SEQUENCE_specifics_t asn_SPC_COUNTValueExtended_specs_1;
extern asn_TYPE_member_t asn_MBR_COUNTValueExtended_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _COUNTValueExtended_H_ */
#include <asn_internal.h>
