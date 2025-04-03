/* Subnet mask parsing function */
void parse_mask(uint32_t msk)
{
  /* Buffer for subnet parts */
  uint16_t msk_part[4];
  /* Extracting subnet mask parts using bitwise operations */
  for(uint8_t i = 0; i < 4; i++)
  {
    msk_part[3 - i] = (msk >> (i * 8)) & 0xFF;
  }
  /* Formatting subnet mask to string */
  sprintf(mask_str, "Msk: %hu.%hu.%hu.%hu\n\r", msk_part[3],
          msk_part[2], msk_part[1], msk_part[0]);
}