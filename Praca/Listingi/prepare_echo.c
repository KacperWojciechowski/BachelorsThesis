/* Funkcja przygotowująca mikrokontroler do wysłania wiadomości echo */
static void prepare_echo(void)
{
  /* Bufor na długość wiadomości - obsługa wiadomości do 99 znaków */
  char byte_count[3];
  /* Bufor na komendę umożliwiającą wysłanie wiadomości */
  char command[20];
  int i;

  /* Sprawdzenie czy otrzymany z modułu komunikat mówi o otrzymaniu
   * przez moduł wiadomości */
  /* Rozpoczęcie od indeksu 2 wynika z offsetu obecnego na początku
   * wiadomości */
  if(data_r[2] == '+' && data_r[3] == 'I' && data_r[4] == 'P'
     && data_r[5] == 'D')
  {
    /* Przypisanie indeksu pierwszej cyfry ilości znaków otrzymanej
     * wiadomości */
    i = 9;
    /* Wyciągnięcie ilości znaków otrzymanej wiadomości */
    while(data_r[i] != ':')
    {
      byte_count[i-9] = data_r[i];
      i++;
    }
    /* Zakończenie ciągu znakowego */
    byte_count[i-9] = '\0';
    /* Ustawienie indeksu pierwszej litery otrzymanej wiadomości */
    i++;
    /* Wyciągnięcie otrzymanej wiadomości */
    while(data_r[i] != 0)
    {
      message[i-11] = data_r[i];
      i++;
    }
    /* Zakończenie wiadomości */
    message[i++]='\r';
    message[i++]='\n';
    message[i] = '\0';
    /* Sformatowanie komendy umożliwiającej wysłanie wiadomości */
    sprintf(command, "AT+CIPSEND=0,%d\r\n", atoi(byte_count));
    /* Wysłanie komendy do modułu */
    HAL_UART_Transmit(&huart6, (uint8_t*)(command), strlen(command), 10);
    /* Ustawienie flagi gotowości do wysłania wiadomości echo */
    ready_to_send=1;
  }
}