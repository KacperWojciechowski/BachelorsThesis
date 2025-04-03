/* DHCP address polling function */
static int is_busy(void)
{
  /* Return variable */
  int ret = 0;
  int i;
  /* Search for "busy" in module feedback */
  for(i = 0; i < sizeof(data_r); i++)
  {
    if(data_r[i] == 'b' && data_r[i+1] == 'u' && data_r[i+2] == 's'
       && data_r[i+3] == 'y')
    {
      /* If the phrase was found, inform that the module is busy
         waiting for DHCP */
      ret = 1;
      break;
    }
  }
  /* Return module busy status */
  return ret;
}