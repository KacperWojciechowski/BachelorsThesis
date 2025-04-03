/* PArsing IP address function */
void parse_ip(uint32_t ip)
{
  /* IP address parts buffer */
  uint16_t ip_part[4];
  /* Extracting IP parts using bitwise operations */
  for(uint8_t i = 0; i < 4; i++)
  {
    ip_part[3 - i] = (ip >> (i * 8)) & 0xFF;
  }
  /* Formatting IP address to string */
  sprintf(ip_str, "IP: %hu.%hu.%hu.%hu\n\r", ip_part[3],
          ip_part[2], ip_part[1], ip_part[0]);
}