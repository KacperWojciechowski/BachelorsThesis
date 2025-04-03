/* Connection accept callback */
static err_t app_callback_accepted(void* arg, struct tcp_pcb* pcb_new, 
                                   err_t err)
{
  struct echo_info* info;

  /* removing unused parameters warning */
  (void)arg;
  (void)err;

  /* Setting new pcb priority */
  tcp_setprio(pcb_new, TCP_PRIO_NORMAL);

  /* Allocating echo_info */
  info = (struct echo_info*)mem_malloc(sizeof(struct echo_info));


  if (info == NULL)
  {
    /* In case of memory error, close connection and propagate 
     * error */
    app_close_connection(pcb_new, info);
    return ERR_MEM;
  }

  /* Setting connection state to accepted */
  info->state = TCP_STATE_ACCEPTED;
  /* Saving pcb pointer */
  info->pcb = pcb_new;
  /* Reset retransmission counter */
  info->retries = 0;
  /* Reset buffer pointer */
  info->p = NULL;

  /* Passing pcb_new as an argument */
  tcp_arg(pcb_new, info);
  /* Registering data receive callback */
  tcp_recv(pcb_new, app_callback_received);
  /* Registering error callback */
  tcp_err(pcb_new, app_callback_error);
  /* Registering polling callback */
  tcp_poll(pcb_new, app_callback_poll, 0);

  return ERR_OK;
}