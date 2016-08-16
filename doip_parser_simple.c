#include <hammer/hammer.h>
#include <hammer/glue.h>

/* This is a simple DoIP parser. It checks the correctness of
 * the general format, but skips internal consistency checks
 * (e.g. the indicated length in not compared to the actual
 * length of the payload).
 */

const HParser *doip = NULL;
const HParser *test_parser_header = NULL;
const HParser *test_parser_payload_type = NULL;
const HParser *test_parser_payload_length = NULL;


/**
 * Make sure the two bytes of the generic header are correct
 * according to SWS_DoIP_00006.
 */
bool check_header(HParseResult *p, void *user_data) {
  // header: byte 0 XOR byte 1 = 0xff
  HParsedToken **header = h_seq_elements(p->ast);
  if ((header[0]->uint ^ header[1]->uint) == 0xff) {
    return true;
  }
  return false;
}

/**
 * Make sure the payload type matches SWS_DoIP_00008 (table 2) and
 * SWS_DoIP_00009 (table 3).
 */
bool check_payload_type(HParseResult *p, void *user_data) {
  switch(p->ast->uint) {
  case 0x0000:  // generic DoIP header negative acknowledge (chapter 7.3.2.1)
    return true;
  case 0x0001:  // vehicle identification request message (chapter 7.3.2.2.1)
    return true;
  case 0x0002:  // vehicle identification request message w. EID (ch 7.3.2.2.2)
    return true;
  case 0x0003:  // vehicle identification request message w. VIN (ch 7.3.2.2.3)
    return true;
  case 0x0004:  // vehicle announcement message/vehicle identification response (ch 7.3.2.2.4)
    return true;
  case 0x0005:  // routing activation request (ch 7.3.2.3.1)
    return true;
  case 0x0006:  // routing activation response (ch 7.3.2.2.4)
    return true;
  case 0x0007:  // alive check request (ch 7.3.2.4.1)
    return true;
  case 0x0008:  // alive check response (ch 7.3.2.4.2)
    return true;
  case 0x4001:  // DoIP entity status request (ch 7.3.2.5.3)
    return true;
  case 0x4002:  // DoIP entity status response (ch 7.3.2.5.4)
    return true;
  case 0x4003:  // diagnostic power mode information request (ch 7.3.2.5.1)
    return true;
  case 0x4004:  // diagnostic power mode information response (ch 7.3.2.5.2)
    return true;
  case 0x8001:  // diagnostic message (ch 7.3.2.6.1)
    return true;
  case 0x8002:  // diagnostic message positive ack (ch 7.3.2.6.2)
    return true;
  case 0x8003:  // diagnostic message negative ack (ch 7.3.2.6.3)
    return true;
  }
  return false;
}

void init_parser(void) {
  HParser *generic_header, *payload_type;
  H_RULE(potential_header, h_repeat_n(h_ch_range(0x00, 0xff),2));
  generic_header = h_attr_bool(potential_header, check_header, NULL);
  test_parser_header = generic_header; // for outside testing

  H_RULE(potential_payload_type, h_uint16());
  payload_type = h_attr_bool(potential_payload_type, check_payload_type, NULL);
  test_parser_payload_type = payload_type;

  H_RULE(payload_length, h_uint32());
  test_parser_payload_length = payload_length;

  H_RULE(message_content, h_many(h_ch_range(0x00, 0xff)));

  H_RULE(generic_message, h_sequence(generic_header,
			  payload_type,
			  payload_length,
			  h_optional(message_content),
			  h_end_p(),
			  NULL
			  ));
  doip = generic_message;
}
