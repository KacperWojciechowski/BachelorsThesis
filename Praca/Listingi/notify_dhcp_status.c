/* Funkcja nadzorująca otrzymanie adresu z DHCP */
void notify_dhcp_status( struct netif *netif)
{
  /* Flaga statusu połączenia */
  static uint8_t connected = 0;

  /* Jeżeli kabel sieciowy jest podłączony, i adres IP jest różny od 0 */
  if (netif_is_link_up(netif) && netif->ip_addr.addr != 0)
  {
    /* Jeżeli wcześniej stan połączenia był rozłączony */
    if (!connected)
    {
      /* Przygotowanie wiadomości o połączeniu */
      sprintf(conn_msg_str, "CONNECTED\n\r");
      /* Przygotowanie wiadomości z adresem IP */
      parse_ip(netif->ip_addr.addr);
      /* Przygotowanie wiadomości z maską sieci */
      parse_mask(netif->netmask.addr);
      /* Przygotowanie wiadomości z adresem bramy */
      parse_gateway(netif->gw.addr);
      /* Ustawienie flagi połączenia */
      connected = 1;
      /* Przesłanie poszczególnych wiadomości za pomocą portu 
       * szeregowego */
      HAL_UART_Transmit(&huart3, (unsigned char*)conn_msg_str, 
                        sizeof(conn_msg_str), 10);
      HAL_UART_Transmit(&huart3, (unsigned char*)ip_str, 
                        sizeof(ip_str), 10);
      HAL_UART_Transmit(&huart3, (unsigned char*)mask_str, 
                        sizeof(mask_str), 10);
      HAL_UART_Transmit(&huart3, (unsigned char*)gw_str, 
                        sizeof(gw_str), 10);
    }
    /* Zgaszenie czerwonej diody i zapalenie zielonej diody jako 
     * sygnalizacja nawiązania połączenia */
    HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
  }
  /* W przypadku odłączenia kabla sieciowego lub nie otrzymaniu adresu 
   * z DHCP routera */
  else
  {
    /* Jeżeli wcześniej stan połączenia był podłączony */
    if (connected)
    {
      /* Przygotowanie wiadomości o rozłączeniu */
      sprintf(conn_msg_str, "DISCONNECTED\n\r");
      /* Zresetowanie adresu IP */
      netif->ip_addr.addr = 0;
      /* Zresetowanie flagi połączenia */
      connected = 0;
      /* Przesłanie wiadomości o rozłączeniu za pomocą portu 
       * szeregowego */
      HAL_UART_Transmit(&huart3, (unsigned char*)conn_msg_str, 
                        sizeof(conn_msg_str), 10);
    }
    /* Zgaszenie zielonej diody i zapalenie czerwonej diody jako 
     * sygnalizacja rozłączenia */
    HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
  }
}