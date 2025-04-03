/* Command count macro */
#define COMMANDS 12

/* Module feedback buffer */
char data_r[1000];
/* Received data buffer */
char message[100];

/* Echo message ready flag */
int ready_to_send = 0;

/* Configuration commands LUT */
char* config[] = {
  "AT+RST\r\n",                             /* Reset module */
  "ATE0\r\n",                               /* Disable command echo */
  "AT\r\n",                                 /* Communication test */
  "AT+GMR\r\n",                             /* Firmware version */
  "AT+CWMODE=1\r\n",                        /* Client operation mode */
  "AT+CIPMODE=0\r\n",                       /* Selecting received data
                                             * format */
  "AT+CIPMUX=1\r\n",                        /* Setting multiconnectivity */
  "AT+CIPSERVER=1,7\r\n",                   /* Enable server and 
                                             * bind to port 7 */
  "AT+CWMODE=?\r\n",                        /* Check operating mode */
  "AT+CWJAP=\"marx\",\"************\"\r\n", /* Connect to Wi-Fi */
  "AT+CIPSTA?\r\n",                         /* Check Wi-Fi connection 
                                             * status */
  "AT+CIFSR\r\n"                            /* Display IP address */
};

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration---------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and 
   * the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  /* Iterate thorugh the configuration commands LUT configuring the module */
  for(i = 0; i < COMMANDS; i++)
  {
    /* Send configuration command */
    HAL_UART_Transmit(&huart6, (uint8_t*)(config[i]), strlen(config[i]), 10);
    /* Clear reception buffer */
    clr_buffer(data_r, 1000);
    /* Receive feedback */
    HAL_UART_Receive(&huart6, (uint8_t*)data_r, sizeof(data_r), 100);

    /* Await for the module wake up after restart */
    if(i == 0)
    {
      HAL_Delay(1000);
    }

    /* Await IP address reception from DHCP */
    while(is_busy())
    {
      /* Await 1 second */
        HAL_Delay(1000);
        /* Querry for IP address, subnet mask and gateway */
      HAL_UART_Transmit(&huart6, (uint8_t*)(config[i]), strlen(config[i]), 
                        10);
      /* Clear reception buffer */
      clr_buffer(data_r, 1000);
      /* Receive feedback */
      HAL_UART_Receive(&huart6, (uint8_t*)data_r, sizeof(data_r), 
                       100);
    }
    /* Transmit received feedback to the overseeing computer
       using serial port */
    HAL_UART_Transmit(&huart3, (unsigned char*)data_r, sizeof(data_r), 
                      10);
    HAL_UART_Transmit(&huart3, (unsigned char*)"\r\n\n", sizeof("\r\n\n"), 
                      10);

  }

  while (1)
  {
    /* USER CODE END WHILE */
    /* Clear reception buffer */
    clr_buffer(data_r, 1000);
    /* Read module feedback */
    HAL_UART_Receive(&huart6, (uint8_t*)data_r, sizeof(data_r), 100);
    /* If echo message is ready to be sent */
    if(ready_to_send)
    {
      /* Send echo data */
      HAL_UART_Transmit(&huart6, (uint8_t*)message, sizeof(message), 10);
      /* Reset echo message ready flag */
      ready_to_send = 0;
    }
    /* Otherwise, if received message is not empty */
    else if (data_r[0] != 0)
    {
      /* Prepare to send an echo data */
      prepare_echo();
      /* Send received feedback through the serial port */
      HAL_UART_Transmit(&huart3, (unsigned char*)data_r, sizeof(data_r), 
                        10);
      HAL_UART_Transmit(&huart3, (unsigned char*)"\r\n\n", 
                        sizeof("\r\n\n"), 10);
    }

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}