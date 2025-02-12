/* Funkcja zwrotna wysyłania */
static err_t app_callback_sent(void* arg, struct tcp_pcb* tpcb, uint16_t len)
{
  /* Wskaźnik na strukturę */
  struct echo_info* info;
  /* Uciszenie ostrzeżeń */
  (void)len;

  /* Zapisanie zrzutowanego wskaźnika na strukturę */
  info = (struct echo_info*) arg;
  /* Wyzerowanie licznika ponownych prób */
  info->retries = 0;

  /* Jeżeli są dane do wysłania */
  if(info->p != NULL)
  {
    /* Zarejestrowanie funkcji zwrotnej wysyłania danych */
    tcp_sent(tpcb, app_callback_sent);
    /* Przesłanie danych */
    app_send_data(tpcb, info);
  }
  /* Jeżeli nie ma danych do wysłania */
  else
  {
    /* Jeżeli stan połączenia jest jako zamykane */
    if(info->state == TCP_STATE_CLOSING)
    {
      /* Zamknięcie połączenia */
      app_close_connection(tpcb, info);
    }
  }
  return ERR_OK;
}