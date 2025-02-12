/* Funkcja czyszczenia buforu odbiorczego */
static void clr_buffer(char* buff, int size)
{
  int i;
  /* Nadpisanie całego buforu wartością 0 */
  for(i = 0; i < size; i++)
  {
    buff[i] = 0;
  }
}