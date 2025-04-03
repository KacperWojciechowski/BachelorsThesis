/* Buffer clear function */
static void clr_buffer(char* buff, int size)
{
  int i;
  /* Overriding entire buffer with default value */
  for(i = 0; i < size; i++)
  {
    buff[i] = 0;
  }
}