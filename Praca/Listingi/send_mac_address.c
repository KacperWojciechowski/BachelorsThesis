/* Funkcja przesyłająca adres MAC urządzenia */
void send_MAC_address(void)
{
  /* Offset dla znaków heksadecymalnych */
  uint8_t hex_offset = 'A' - 10;
  /* Offset dla znaków dziesiętnych */
  uint8_t dec_offset = '0';
  /* Bufor znaków adresu MAC */
  char mac_part[12];

  /* Iteracja przez adres MAC */
  for(uint8_t i = 0; i < 6; i++)
  {
    /* Wyciągnięcie wartości znaków adresu MAC */
    mac_part[i*2] = (gnetif.hwaddr[i] & 0xF0) >> 4;
    mac_part[i*2+1] = gnetif.hwaddr[i] & 0x0F;

    /* Sformatowanie otrzymanych wartości do postaci znakowych */
    if(mac_part[i*2] > 10) mac_part[i*2] += hex_offset;
    else mac_part[i*2] += dec_offset;

    if(mac_part[i*2+1] > 10) mac_part[i*2+1] += hex_offset;
    else mac_part[i*2+1] += dec_offset;
  }
  /* Sformatowanie znaków do wiadomości z adresem MAC */
  sprintf(mac_str, "MAC: %c%c:%c%c:%c%c:%c%c:%c%c:%c%c\n\n\r",
          mac_part[0], mac_part[1],
          mac_part[2], mac_part[3],
          mac_part[4], mac_part[5],
          mac_part[6], mac_part[7],
          mac_part[8], mac_part[9],
          mac_part[10], mac_part[11]);
  /* Przesłanie adresu MAC za pomocą portu szeregowego */
  HAL_UART_Transmit(&huart3, (unsigned char*)mac_str, sizeof(mac_str), 10);
}