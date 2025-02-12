void MX_LWIP_Process(void)
{
  /* USER CODE BEGIN 4_1 */
  /* USER CODE END 4_1 */
  ethernetif_input(&gnetif);

  /* USER CODE BEGIN 4_2 */
  /* USER CODE END 4_2 */
  /* Handle timeouts */
  sys_check_timeouts();

  /* USER CODE BEGIN 4_3 */
  ethernetif_set_link(&gnetif);
  /* Jeżeli kabel sieciowy jest podłączony, i nie ustawiono połączenia */
  if(netif_is_link_up(&gnetif) && ! netif_is_up(&gnetif))
  {
    /* Ustawienie połączenia */
    netif_set_up(&gnetif);
    /* Pobór adresu z DHCP routera */
    dhcp_start(&gnetif);
  }
  /* USER CODE END 4_3 */
}