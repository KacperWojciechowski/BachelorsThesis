/* Data receive callback */
static err_t app_callback_received(void* arg, struct tcp_pcb* tpcb,
                                   struct pbuf* p, err_t err)
{
  /* echo_info pointer */
  struct echo_info* info;
  /* error data variable */
  err_t ret_err;

  /* Asserting echo_info is not null */
  LWIP_ASSERT("arg != NULL", arg != NULL);
  /* Downcasting the parameter pointer to echo_info pointer */
  info = (struct echo_info*) arg;

  /* If there is no data to be sent */
  if(p == NULL)
  {
    /* Change connection state to closing */
    info->state = TCP_STATE_CLOSING;
    /* If data buffer is null */
    if(info->p == NULL)
    {
      /* Close connection */
      app_close_connection(tpcb, info);
    }
    /* If there is data to be sent */
    else
    {
      /* Registering data send callback */
      tcp_sent(tpcb, app_callback_sent);
      /* Transferring data */
      app_send_data(tpcb, info);
    }
    ret_err = ERR_OK;
  }
  /* If there was a reception error */
  else if(err != ERR_OK)
  {
    /* If buffer is present */
    if(p != NULL)
    {
      /* Clearing reception buffer */
      info->p = NULL;
      /* Freeing the buffer */
      pbuf_free(p);
    }
    /* Saving error info */
    ret_err = err;
  }
  /* Reception of first batch of data */
  else if (info->state == TCP_STATE_ACCEPTED)
  {
    /* Changing connection status to received */
    info->state = TCP_STATE_RECEIVED;
    /* Saving buffer into the echo_info structure */
    info->p = p;
    /* Registering data send callback */
    tcp_sent(tpcb, app_callback_sent);
    /* Transmitting data */
    app_send_data(tpcb, info);
    ret_err = ERR_OK;
  }
  /* Reception of subsequent data */
  else if (info->state == TCP_STATE_RECEIVED)
  {
    /* If the buffer is absent */
    if(info->p == NULL)
    {
      /* Saving buffer into the structure */
      info->p = p;
      /* Data transmission */
      app_send_data(tpcb, info);
    }
    /* If there is data to be send, but structure
       buffer is not empty */
    else
    {
      /* Creating pointer to the buffer */
      struct pbuf* ptr = info->p;
      /* Appending the buffer */
      pbuf_chain(ptr, p);
    }
    ret_err = ERR_OK;
  }
  /* Data reception when connection is being closed */
  else if(info->state == TCP_STATE_CLOSING)
  {
    /* Recommending the window size */
    tcp_recved(tpcb, p->tot_len);
    /* Clearing and freeing the buffer */
    info->p = NULL;
    pbuf_free(p);
    ret_err = ERR_OK;
  }
  /* Reception done */
  else
  {
    /* Recommending the window size */
    tcp_recved(tpcb, p->tot_len);
    /* Clearing and freeing the buffer */
    info->p = NULL;
    pbuf_free(p);
    ret_err = ERR_OK;
  }
  return ret_err;
}