/*
 * echo.h
 *
 *  Created on: Oct 17, 2021
 *      Author: Kacper Wojciechowski
 */

#ifndef INC_ECHO_H_
#define INC_ECHO_H_

#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"

/* Echo server states */
enum tcp_state_enum {
  TCP_STATE_NONE = 0,
  TCP_STATE_ACCEPTED,
  TCP_STATE_RECEIVED,
  TCP_STATE_CLOSING
};

/* Echo server info */
struct echo_info {
  uint8_t state;       // state
  uint8_t retries;     // retransmission counter
  struct tcp_pcb* pcb; // PCB pointer
  struct pbuf* p;      // packet buffer
};

err_t init_echo(void);


#endif /* INC_ECHO_H_ */