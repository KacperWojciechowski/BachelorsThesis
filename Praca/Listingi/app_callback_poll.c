/* Polling callback */
static err_t app_callback_poll(void* arg, struct tcp_pcb* tpcb)
{
  /* Pointer to echo_info */
  struct echo_info* info;
  /* Downcasting echo_info pointer */
  info = (struct echo_info*) arg;
  /* If it did not downcast properly */
  if(info == NULL)
  {
    /* Aborting the connection and returning an error */
    tcp_abort(tpcb);
    return ERR_ABRT;
  }
  /* If there is data to transmit */
  if(info->p != NULL)
  {
    /* Registering data send callback */
    tcp_sent(tpcb, app_callback_sent);
    /* Sending data */
    app_send_data(tpcb, info);
  }
  /* If there is no data to be sent */
  else
  {
    /* If connection is being closed */
    if(info->state == TCP_STATE_CLOSING)
    {
      /* Disconnecting */
      app_close_connection(tpcb, info);
    }
  }
  return ERR_OK;
}