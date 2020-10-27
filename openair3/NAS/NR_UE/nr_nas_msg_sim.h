/*! \file nr_nas_msg_sim.h

\brief simulator for nr nas message
\author Yoshio INOUE, Masayuki HARADA
\email: yoshio.inoue@fujitsu.com,masayuki.harada@fujitsu.com
\date 2020
\version 0.1
*/


#ifndef __NR_NAS_MSG_SIM_H__
#define __NR_NAS_MSG_SIM_H__

#include "RegistrationRequest.h"
#include "as_message.h"


#define PLAIN_5GS_MSG                                      0b0000
#define INTEGRITY_PROTECTED                                0b0001

#define REGISTRATION_REQUEST                               0b01000001 /* 65 = 0x41 */
#define INITIAL_REGISTRATION                               0b001


typedef enum fgs_protocol_discriminator_e {
  /* Protocol discriminator identifier for 5GS Mobility Management */
  FGS_MOBILITY_MANAGEMENT_MESSAGE =   0x7E,

  /* Protocol discriminator identifier for 5GS Session Management */
  FGS_SESSION_MANAGEMENT_MESSAGE =    0x2E,
} fgs_protocol_discriminator_t;


typedef struct {
  uint8_t ex_protocol_discriminator;
  uint8_t security_header_type;
  uint8_t message_type;
} mm_msg_header_t;

/* Structure of security protected header */
typedef struct {
  fgs_protocol_discriminator_t    protocol_discriminator;
  uint8_t                         security_header_type;
  uint32_t                        message_authentication_code;
  uint8_t                         sequence_number;
} fgs_nas_message_security_header_t;

typedef union {
  mm_msg_header_t                        header;
  registration_request_msg               registration_request;
} MM_msg;



typedef struct {
  MM_msg mm_msg;    /* 5GS Mobility Management messages */
} fgs_nas_message_plain_t;

typedef struct {
  fgs_nas_message_security_header_t header;
  fgs_nas_message_plain_t plain;
} fgs_nas_message_security_protected_t;


typedef union {
  fgs_nas_message_security_header_t header;
  fgs_nas_message_security_protected_t security_protected;
  fgs_nas_message_plain_t plain;
} fgs_nas_message_t;

void generateRegistrationRequest(as_nas_info_t *initialNasMsg);

#endif /* __NR_NAS_MSG_SIM_H__*/