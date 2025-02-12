/* Funkcja zamieniąca maskę na ciąg znakowy */
void parse_mask(uint32_t msk)
{
  /* Bufor na części maski */
  uint16_t msk_part[4];
  /* Wyciągnięcie części maski za pomocą operacji bitowych */
  for(uint8_t i = 0; i < 4; i++)
  {
    msk_part[3 - i] = (msk >> (i * 8)) & 0xFF;
  }
  /* Sformatowanie maski do postaci ciągu znakowego */
  sprintf(mask_str, "Msk: %hu.%hu.%hu.%hu\n\r", msk_part[3],
          msk_part[2], msk_part[1], msk_part[0]);
}