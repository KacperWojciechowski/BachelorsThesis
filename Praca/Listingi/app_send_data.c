/* Data transmission callback */
static void app_send_data(struct tcp_pcb* tpcb, struct echo_info* info)
{
  /* Buffor for data to be sent */
  struct pbuf* ptr;
  err_t wr_err = ERR_OK;

  /* As long as no error occured, there is data to be sent, and
     data length is less than the send buffer length */
  while((wr_err == ERR_OK) && (info->p != NULL)
        && (info->p->len <= tcp_sndbuf(tpcb)))
  {
    /* Copying the buffer pointer */
    ptr = info->p;
    /* Data transmission */
    wr_err = tcp_write(tpcb, ptr->payload, ptr->len,
                       TCP_WRITE_FLAG_COPY);

    /* If data was sent successfully */
    if(wr_err == ERR_OK)
    {
      /* Variable for the buffer length */
      uint16_t plen;
      uint8_t freed;

      /* Saving the buffer length */
      plen = ptr->len;
      /* Moving buffer to the next packet */
      info->p = ptr->next;

      /* If there is a chain buffer */
      if(info->p != NULL)
      {
        /* Increase reference counter */
        pbuf_ref(info->p);
      }

      do
      {
        /* Free the old buffer */
        freed = pbuf_free(ptr);
      }
      while(freed == 0);

      /* Recommending window size */
      tcp_recved(tpcb, plen);
    }
    /* If transmission failed */
    else
    {
      /* Recovering the buffer pointer */
      info->p = ptr;
      /* Increasing the retransmission counter */
      info->retries++;
    }
  }
}