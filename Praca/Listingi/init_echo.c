/* Echo server initialization function */
err_t init_echo()
{
  err_t err;
  pcb_server = tcp_new(); // allocating pcb memory

  if(pcb_server == NULL)
  {
    /* In case of lack of memory, free allocated memory and
       return an error */
    memp_free(MEMP_TCP_PCB, pcb_server);
    return ERR_MEM;
  }

  /* Bind server to port 7 */
  err = tcp_bind(pcb_server, IP_ADDR_ANY, 7);
  if (err != ERR_OK)
  {
    /* In case binding fails, free memory and return 
       an error */
    memp_free(MEMP_TCP_PCB, pcb_server);
    return err;
  }

  /* Listening */
  pcb_server = tcp_listen(pcb_server);
  /* Registering connection accept callback */
  tcp_accept(pcb_server, app_callback_accepted);

  return ERR_OK;
}