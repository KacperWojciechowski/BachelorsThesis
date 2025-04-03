/* Sending callback */
static err_t app_callback_sent(void* arg, struct tcp_pcb* tpcb, uint16_t len)
{
  /* Pointer to the echo_info struct */
  struct echo_info* info;
  /* Silencing warnings */
  (void)len;

  /* Downcasting the echo_info pointer */
  info = (struct echo_info*) arg;
  /* Resetting the retransmission counter */
  info->retries = 0;

  /* If there is data to be sent */
  if(info->p != NULL)
  {
    /* Registering the send callback */
    tcp_sent(tpcb, app_callback_sent);
    /* Data transmission */
    app_send_data(tpcb, info);
  }
  /* If there is no data to be sent */
  else
  {
    /* If the connection is being closed */
    if(info->state == TCP_STATE_CLOSING)
    {
      /* Closing the connection */
      app_close_connection(tpcb, info);
    }
  }
  return ERR_OK;
}