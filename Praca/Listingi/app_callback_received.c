/* Funkcja zwrotna odbioru wiadomości */
static err_t app_callback_received(void* arg, struct tcp_pcb* tpcb,
                                   struct pbuf* p, err_t err)
{
  /* Wskaźnik na strukturę echo_info */
  struct echo_info* info;
  /* Zmienna informacji o błędach */
  err_t ret_err;

  /* Sprawdzenie czy argument jest różny od NULL */
  LWIP_ASSERT("arg != NULL", arg != NULL);
  /* Zapisanie zrzutowanego wskaźnika na strukturę echo_info */
  info = (struct echo_info*) arg;

  /* Jeżeli funkcja została wywołana, ale nie ma danych */
  if(p == NULL)
  {
    /* Ustawienie stanu połączenia na zamykane */
    info->state = TCP_STATE_CLOSING;
    /* Jeżeli bufor struktury jest NULL */
    if(info->p == NULL)
    {
      /* Zamknięcie połączenia */
      app_close_connection(tpcb, info);
    }
    /* Jeżeli w buforze struktury są dane do przesłania */
    else
    {
      /* Zarejestrowanie funkcji zwrotnej wysyłania danych */
      tcp_sent(tpcb, app_callback_sent);
      /* Przesłanie danych */
      app_send_data(tpcb, info);
    }
    ret_err = ERR_OK;
  }
  /* Jeśli wystąpił błąd przy odbiorze */
  else if(err != ERR_OK)
  {
    /* Jeżeli bufor nie jest pusty */
    if(p != NULL)
    {
      /* Wyczyszczenie buforu struktury */
      info->p = NULL;
      /* Zwolnienie buforu */
      pbuf_free(p);
    }
    /* Zapisanie informacji o błędzie */
    ret_err = err;
  }
  /* Odbiór pierwszych danych */
  else if (info->state == TCP_STATE_ACCEPTED)
  {
    /* Zmiana statusu na odebrano */
    info->state = TCP_STATE_RECEIVED;
    /* Zapisanie buforu w strukturze */
    info->p = p;
    /* Zarejestrowanie funkcji zwrotnej wysyłania danych */
    tcp_sent(tpcb, app_callback_sent);
    /* Przesłanie danych */
    app_send_data(tpcb, info);
    ret_err = ERR_OK;
  }
  /* Odbiór kolejnych danych */
  else if (info->state == TCP_STATE_RECEIVED)
  {
    /* Jeżeli nie ma danych do wysłania */
    if(info->p == NULL)
    {
      /* Zapisanie buforu w strukturze */
      info->p = p;
      /* Wysłanie danych */
      app_send_data(tpcb, info);
    }
    /* Jeżeli są dane do przesłania, a bufor struktury nie jest 
     * pusty */
    else
    {
      /* Utworzenie wskaźnika na bufor struktury */
      struct pbuf* ptr = info->p;
      /* Dołączenie do buforu struktury buforu otrzymanych 
       * danych */
      pbuf_chain(ptr, p);
    }
    ret_err = ERR_OK;
  }
  /* Odbiór danych w trakcie zamykania */
  else if(info->state == TCP_STATE_CLOSING)
  {
    /* Rekomendowanie rozmiaru okna */
    tcp_recved(tpcb, p->tot_len);
    /* Wyczyszczenie i zwolnienie buforów */
    info->p = NULL;
    pbuf_free(p);
    ret_err = ERR_OK;
  }
  /* Odbiór zakończony */
  else
  {
    /* Rekomendowanie rozmiaru okna */
    tcp_recved(tpcb, p->tot_len);
    /* Wyczyszczenie i zwolnienie buforów */
    info->p = NULL;
    pbuf_free(p);
    ret_err = ERR_OK;
  }
  return ret_err;
}