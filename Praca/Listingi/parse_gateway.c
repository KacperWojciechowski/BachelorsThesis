/* Gateway address parsing function */
void parse_gateway(uint32_t gw)
{
  /* Gateway address parts buffer */
  uint16_t gw_part[4];
  /* Extracting gateway parts using bitwise operations */
  for(uint8_t i = 0; i < 4; i++)
  {
    gw_part[3 - i] = (gw >> (i * 8)) & 0xFF;
  }
  /* Formatting gateway to string format */
  sprintf(gw_str, "Gw: %hu.%hu.%hu.%hu\n\r", gw_part[3],
          gw_part[2], gw_part[1], gw_part[0]);
}