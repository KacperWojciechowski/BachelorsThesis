/* Function transferring MAC address */
void send_MAC_address(void)
{
  /* Offset for hexadecimal characters */
  uint8_t hex_offset = 'A' - 10;
  /* Offset for decimal characters */
  uint8_t dec_offset = '0';
  /* MAC address char buffer */
  char mac_part[12];

  /* Iterating through MAC */
  for(uint8_t i = 0; i < 6; i++)
  {
    /* Extracting MAC address chars */
    mac_part[i*2] = (gnetif.hwaddr[i] & 0xF0) >> 4;
    mac_part[i*2+1] = gnetif.hwaddr[i] & 0x0F;

    /* Formatting MAC values to character representation */
    if(mac_part[i*2] > 10) mac_part[i*2] += hex_offset;
    else mac_part[i*2] += dec_offset;

    if(mac_part[i*2+1] > 10) mac_part[i*2+1] += hex_offset;
    else mac_part[i*2+1] += dec_offset;
  }
  /* Formatting MAC into a message */
  sprintf(mac_str, "MAC: %c%c:%c%c:%c%c:%c%c:%c%c:%c%c\n\n\r",
          mac_part[0], mac_part[1],
          mac_part[2], mac_part[3],
          mac_part[4], mac_part[5],
          mac_part[6], mac_part[7],
          mac_part[8], mac_part[9],
          mac_part[10], mac_part[11]);
  /* Sending MAC through the serial port */
  HAL_UART_Transmit(&huart3, (unsigned char*)mac_str, sizeof(mac_str), 10);
}