/* Funkcja zamykająca połączenie */
static void app_close_connection(struct tcp_pcb* tpcb, struct echo_info* info)
{
  /* Wyczyszczenie funkcji zwrotnych */
  tcp_arg(tpcb, NULL);
  tcp_sent(tpcb, NULL);
  tcp_recv(tpcb, NULL);
  tcp_err(tpcb, NULL);
  tcp_poll(tpcb, NULL, 0);

  /* Jeżeli zapisano strukturę */
  if(info != NULL)
  {
    /* Zwolnienie zaalokowanej pamięci */
    mem_free(info);
  }

  /* Zamknięcie połączenia */
  tcp_close(tpcb);
}