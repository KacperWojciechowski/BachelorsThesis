/* Funkcja zwrotna nasłuchu */
static err_t app_callback_poll(void* arg, struct tcp_pcb* tpcb)
{
  /* Wskaźnik na strukturę */
  struct echo_info* info;
  /* Zapisanie zrzutowanego wskaźnika na strukturę */
  info = (struct echo_info*) arg;
  /* Jeżeli nie ma struktury */
  if(info == NULL)
  {
    /* Przerwanie połączenia i zwrócenie błędu */
    tcp_abort(tpcb);
    return ERR_ABRT;
  }
  /* Jeśli są dane do przesłania */
  if(info->p != NULL)
  {
    /* Zarejestrowanie funkcji zwrotnej wysyłania danych */
    tcp_sent(tpcb, app_callback_sent);
    /* Przesłanie danych */
    app_send_data(tpcb, info);
  }
  /* Jeśli nie ma danych do przesłania */
  else
  {
    /* Jeżeli status połączenia jest jako zamykane */
    if(info->state == TCP_STATE_CLOSING)
    {
      /* Zamknięcie połączenia */
      app_close_connection(tpcb, info);
    }
  }
  return ERR_OK;
}