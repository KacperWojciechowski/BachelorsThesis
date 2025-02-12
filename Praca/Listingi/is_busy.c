/* Funkcja oczekująca na uzyskanie adresu z DHCP routera */
static int is_busy(void)
{
  /* Zmienna na wartość zwracaną */
  int ret = 0;
  int i;
  /* Wyszukaj frazę "busy" w otrzymanym z modułu komunikacie */
  for(i = 0; i < sizeof(data_r); i++)
  {
    if(data_r[i] == 'b' && data_r[i+1] == 'u' && data_r[i+2] == 's'
       && data_r[i+3] == 'y')
    {
      /* Jeśli znaleziono frazę, zwróć informację że moduł jest
       * zajęty oczekiwaniem na DHCP */
      ret = 1;
      break;
    }
  }
  /* Zwróć informację o zajętości modułu */
  return ret;
}