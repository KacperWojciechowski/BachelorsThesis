/* Funkcja inicjalizująca serwer echo */
err_t init_echo()
{
  err_t err;
  pcb_server = tcp_new(); // alokacja pamięci pcb

  if(pcb_server == NULL)
  {
    /* W przypadku braku pamięci, zwolnienie zaalokowanej pamięci
     * i zwrócenie błędu */
    memp_free(MEMP_TCP_PCB, pcb_server);
    return ERR_MEM;
  }

  /* Powiązanie serwera z portem 7 */
  err = tcp_bind(pcb_server, IP_ADDR_ANY, 7);
  if (err != ERR_OK)
  {
    /* W przypadku błędu powiązania, zwolnienei pamieci i zwrócenie 
     * błędu */
    memp_free(MEMP_TCP_PCB, pcb_server);
    return err;
  }

  /* Nasłuchiwanie */
  pcb_server = tcp_listen(pcb_server);
  /* Zarejestrowanie funkcji zwrotnej zaakceptowania połączenia */
  tcp_accept(pcb_server, app_callback_accepted);

  return ERR_OK;
}