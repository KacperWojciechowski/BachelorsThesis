/* Connection close callback */
static void app_close_connection(struct tcp_pcb* tpcb, struct echo_info* info)
{
  /* De-registering callbacks */
  tcp_arg(tpcb, NULL);
  tcp_sent(tpcb, NULL);
  tcp_recv(tpcb, NULL);
  tcp_err(tpcb, NULL);
  tcp_poll(tpcb, NULL, 0);

  /* If echo_info is present */
  if(info != NULL)
  {
    /* Freeing the memory */
    mem_free(info);
  }

  /* Closing connection */
  tcp_close(tpcb);
}