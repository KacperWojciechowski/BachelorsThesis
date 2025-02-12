/* Funkcja przesyłu danych */
static void app_send_data(struct tcp_pcb* tpcb, struct echo_info* info)
{
  /* Bufor na dane do wysłania */
  struct pbuf* ptr;
  err_t wr_err = ERR_OK;

  /* Dopóki nie napotkano błędu, są dane do wysłania, i długość danych
   * jest mniejsza niż długość buforu wysyłkowego */
  while((wr_err == ERR_OK) && (info->p != NULL)
        && (info->p->len <= tcp_sndbuf(tpcb)))
  {
    /* Przepisanie wskaźnika na bufor */
    ptr = info->p;
    /* Przesłanie danych */
    wr_err = tcp_write(tpcb, ptr->payload, ptr->len,
                       TCP_WRITE_FLAG_COPY);

    /* Jeżeli dane zostały przesłane prawidłowo */
    if(wr_err == ERR_OK)
    {
      /* Zmienna na długość bufora */
      uint16_t plen;
      uint8_t freed;

      /* Zapisanie długości bufora */
      plen = ptr->len;
      /* Przestawienie bufora na następny pakiet */
      info->p = ptr->next;

      /* Jest do przesłania bufor łańcuchowy */
      if(info->p != NULL)
      {
        /* Zwiększenie wskaźnika referencyjnego */
        pbuf_ref(info->p);
      }

      do
      {
        /* Zwolnienie starego bufora */
        freed = pbuf_free(ptr);
      }
      while(freed == 0);

      /* Rekomendowanie rozmiaru okna */
      tcp_recved(tpcb, plen);
    }
    /* Jeżeli nie udało się przesłać danych */
    else
    {
      /* Odzyskanie wskaźnika na bufor */
      info->p = ptr;
      /* Zwiększenie licznika powtórzeń transmisji */
      info->retries++;
    }
  }
}