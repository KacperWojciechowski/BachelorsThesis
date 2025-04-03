/* DHCP address querrying callback */
void notify_dhcp_status( struct netif *netif)
{
  /* Connection status flag */
  static uint8_t connected = 0;

  /* If network cable is connected and IP is different from 0x0 */
  if (netif_is_link_up(netif) && netif->ip_addr.addr != 0)
  {
    /* If previous state was disconnected */
    if (!connected)
    {
      /* Prepare connected message */
      sprintf(conn_msg_str, "CONNECTED\n\r");
      /* Prepare IP address message */
      parse_ip(netif->ip_addr.addr);
      /* Prepare subnet mask message */
      parse_mask(netif->netmask.addr);
      /* Prepare gateway message */
      parse_gateway(netif->gw.addr);
      /* Set connection flag */
      connected = 1;
      /* Transmit all the data via serial port */
      HAL_UART_Transmit(&huart3, (unsigned char*)conn_msg_str, 
                        sizeof(conn_msg_str), 10);
      HAL_UART_Transmit(&huart3, (unsigned char*)ip_str, 
                        sizeof(ip_str), 10);
      HAL_UART_Transmit(&huart3, (unsigned char*)mask_str, 
                        sizeof(mask_str), 10);
      HAL_UART_Transmit(&huart3, (unsigned char*)gw_str, 
                        sizeof(gw_str), 10);
    }
    /* Turn the red LED off and set green LED on to signalize
       the connection has been established */
    HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
  }
  /* In case the network cable is disconnected or DHCP does not provide
     an IP address */
  else
  {
    /* If previous state was connected */
    if (connected)
    {
      /* Prepare disconnected message */
      sprintf(conn_msg_str, "DISCONNECTED\n\r");
      /* Reset IP address */
      netif->ip_addr.addr = 0;
      /* Reset connection flag */
      connected = 0;
      /* Transmit disconection message via serial port */
      HAL_UART_Transmit(&huart3, (unsigned char*)conn_msg_str, 
                        sizeof(conn_msg_str), 10);
    }
    /* Turn off green LED and turn on red LED to signalize
       disconnection */
    HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
  }
}