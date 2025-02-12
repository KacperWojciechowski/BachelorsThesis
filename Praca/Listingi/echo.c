/*
 * echo.c
 *
 *  Created on: Oct 17, 2021
 *      Author: Kacper Wojciechowski
 */

#include "echo.h"

static struct tcp_pcb* pcb_server; // echoserver pcb

/* Funkcje callback dla stosu LwIP */
static err_t app_callback_accepted(void* arg, struct tcp_pcb* pcb_new, 
                                   err_t err);
static err_t app_callback_received(void* arg, struct tcp_pcb* tpcb, 
                                   struct pbuf* p, err_t err);
static void app_callback_error(void* arg, err_t err);
static err_t app_callback_sent(void* arg, struct tcp_pcb* tpcb, 
                               uint16_t len);
static err_t app_callback_poll(void* arg, struct tcp_pcb* tpcb);

/* Funkcje użytkowe */
static void app_send_data(struct tcp_pcb* tpcb, struct echo_info* info);
static void app_close_connection(struct tcp_pcb* tpcb,
                                 struct echo_info* info);