#pragma once

#include <stdint.h>

#include "frame.h"

#define RTP_PAYLOAD_SIZE 2035

typedef struct /* 13 bytes + RTP_PAYLOAD_SIZE */
{
        /* RTP Header, RFC 3550 */
#ifdef BIG_ENDIAN
        uint16_t version     : 2; /* RTP version (2) */
        uint16_t padding     : 1; /* Padding bit (0) */
        uint16_t extension   : 1; /* Extension bit (0) */
        uint16_t csrccount   : 4; /* CSRC identifiers count (0) */
        uint16_t marker      : 1; /* Set for the last packet of each encoded frame */
        uint16_t payloadtype : 7; /* VP8/9 Payload type (dynamically negotiated 96-127), RFC 3551 */
#else
        uint16_t payloadtype : 7;
        uint16_t marker      : 1;
        uint16_t csrccount   : 4;
        uint16_t extension   : 1;
        uint16_t padding     : 1;
        uint16_t version     : 2;
#endif
        uint16_t seqnum;          /* Sequence number */
        uint32_t timestamp;       /* 90Hz resolution timestamp */
        uint32_t ssrc;            /* Synchronization source identifier */
        /* Optional fields */

        /* VP8 Payload descriptor, draft-ietf-payload-vp8-09 */
#ifdef BIG_ENDIAN
        uint8_t extended  : 1; /* Extended control bit (0) */
        uint8_t reserved0 : 1; /* Reserved for future use (0) */
        uint8_t nonref    : 1; /* Non reference frame */
        uint8_t pstart    : 1; /* VP8 Partition start bit */
        uint8_t reserved1 : 1; /* Reserved for future use (0) */
        uint8_t pid       : 3; /* Partition index */
#else
        uint8_t pid       : 3;
        uint8_t reserved1 : 1;
        uint8_t pstart    : 1;
        uint8_t nonref    : 1;
        uint8_t reserved0 : 1;
        uint8_t extended  : 1;
#endif
        /* Optional fields */

        union
        {
                rtvs_frame_header_t header;
                unsigned char       data[RTP_PAYLOAD_SIZE];
        } payload;

} rtvs_packet_t;
