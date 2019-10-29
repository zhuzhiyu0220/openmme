/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "S1AP-IEs"
 * 	found in "./asn1c/S1AP-IEs.asn"
 * 	`asn1c -fcompound-names -fno-include-deps -gen-PER -findirect-choice -pdu=S1AP-PDU`
 */

#ifndef	_V2XServicesAuthorized_H_
#define	_V2XServicesAuthorized_H_


#include <asn_application.h>

/* Including external dependencies */
#include "VehicleUE.h"
#include "PedestrianUE.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct ProtocolExtensionContainer;

/* V2XServicesAuthorized */
typedef struct V2XServicesAuthorized {
	VehicleUE_t	*vehicleUE;	/* OPTIONAL */
	PedestrianUE_t	*pedestrianUE;	/* OPTIONAL */
	struct ProtocolExtensionContainer	*iE_Extensions;	/* OPTIONAL */
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} V2XServicesAuthorized_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_V2XServicesAuthorized;
extern asn_SEQUENCE_specifics_t asn_SPC_V2XServicesAuthorized_specs_1;
extern asn_TYPE_member_t asn_MBR_V2XServicesAuthorized_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _V2XServicesAuthorized_H_ */
#include <asn_internal.h>
