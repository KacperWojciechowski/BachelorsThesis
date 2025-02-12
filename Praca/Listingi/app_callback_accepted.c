/* Funkcja zwrotna zaakceptowania połączenia */
static err_t app_callback_accepted(void* arg, struct tcp_pcb* pcb_new, 
                                   err_t err)
{
  struct echo_info* info;

  /* usunięcie ostrzeżeń */
  (void)arg;
  (void)err;

  /* Ustawienie priorytetu nowego pcb */
  tcp_setprio(pcb_new, TCP_PRIO_NORMAL);

  /* alokacja struktury echo_info */
  info = (struct echo_info*)mem_malloc(sizeof(struct echo_info));


  if (info == NULL)
  {
    /* W przypadku braku pamięci, zamknięcie połączenia i zwrócenie 
     * błędu */
    app_close_connection(pcb_new, info);
    return ERR_MEM;
  }

  /* Ustawienie stanu połączenia na zaakceptowane */
  info->state = TCP_STATE_ACCEPTED;
  /* Zapisanie wskaźnika na pcb */
  info->pcb = pcb_new;
  /* Wyzerowanie licznika */
  info->retries = 0;
  /* Wyczyszczenie wskaźnika na bufor */
  info->p = NULL;

  /* Przesłanie struktury pcb_new jako argument */
  tcp_arg(pcb_new, info);
  /* Zarejestrowanie funkcji zwrotnej odbioru wiadomości */
  tcp_recv(pcb_new, app_callback_received);
  /* Zarejestrowanie funkcji zwrotnej błędu */
  tcp_err(pcb_new, app_callback_error);
  /* Zarejestrowanie funkcji zwrotnej nasłuchiwania */
  tcp_poll(pcb_new, app_callback_poll, 0);

  return ERR_OK;
}