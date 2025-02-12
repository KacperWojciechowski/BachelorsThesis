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

/* Stany serwera echo */
enum tcp_state_enum {
  TCP_STATE_NONE = 0,
  TCP_STATE_ACCEPTED,
  TCP_STATE_RECEIVED,
  TCP_STATE_CLOSING
};

/* Info serwera echo */
struct echo_info {
  uint8_t state;       // stan
  uint8_t retries;     // licznik powtórzeń
  struct tcp_pcb* pcb; // wskaźnik PCB
  struct pbuf* p;      // bufor pakietów
};

err_t init_echo(void);


#endif /* INC_ECHO_H_ */