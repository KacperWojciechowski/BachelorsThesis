/* Funkcja zamieniająca bramę na ciąg znakowy */
void parse_gateway(uint32_t gw)
{
  /* Bufor na części bramy */
  uint16_t gw_part[4];
  /* Wyciągnięcie części bramy za pomocą operacji bitowych */
  for(uint8_t i = 0; i < 4; i++)
  {
    gw_part[3 - i] = (gw >> (i * 8)) & 0xFF;
  }
  /* Sformatowanie bramy do postaci ciągu znakowego */
  sprintf(gw_str, "Gw: %hu.%hu.%hu.%hu\n\r", gw_part[3],
          gw_part[2], gw_part[1], gw_part[0]);
}