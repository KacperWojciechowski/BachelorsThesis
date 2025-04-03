/* Prepare microcontroller for sending echo messages */
static void prepare_echo(void)
{
  /* Message length buffer - messages up to 99 chars */
  char byte_count[3];
  /* Data send command buffer */
  char command[20];
  int i;

  /* Checking whether feedback from the module informs about
     receiving a message by the module */
  /* Starting from index 2 is a result of an offset present at
     the message start */
  if(data_r[2] == '+' && data_r[3] == 'I' && data_r[4] == 'P'
     && data_r[5] == 'D')
  {
    /* Assigning index of the first digit of char count in
       received message */
    i = 9;
    /* Extracting char count from received message */
    while(data_r[i] != ':')
    {
      byte_count[i-9] = data_r[i];
      i++;
    }
    /* Closing the string */
    byte_count[i-9] = '\0';
    /* Setting the index of first letter of received message */
    i++;
    /* Extracting received message */
    while(data_r[i] != 0)
    {
      message[i-11] = data_r[i];
      i++;
    }
    /* Closing the message */
    message[i++]='\r';
    message[i++]='\n';
    message[i] = '\0';
    /* Formatting the command for sending data */
    sprintf(command, "AT+CIPSEND=0,%d\r\n", atoi(byte_count));
    /* Send command to the module */
    HAL_UART_Transmit(&huart6, (uint8_t*)(command), strlen(command), 10);
    /* Set ready flag to send an echo message */
    ready_to_send=1;
  }
}