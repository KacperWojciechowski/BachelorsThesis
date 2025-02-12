/* Makro określające ilość komend konfiguracyjnych */
#define COMMANDS 12

/* Bufor odbieranych komunikatów od modułu */
char data_r[1000];
/* Bufor odebranej wiadomości */
char message[100];

/* Flaga gotowości do wysłania wiadomości echo */
int ready_to_send = 0;

/* Tablica komend konfiguracyjnych modułu */
char* config[] = {
  "AT+RST\r\n",                             /* Zresetuj moduł */
  "ATE0\r\n",                               /* Wyłącz echo komend */
  "AT\r\n",                                 /* Test komunikacji */
  "AT+GMR\r\n",                             /* Wersja oprogramowania */
  "AT+CWMODE=1\r\n",                        /* Tryb pracy jako klient */
  "AT+CIPMODE=0\r\n",                       /* Wybranie formatu odbieranych
                                             * wiadomości */
  "AT+CIPMUX=1\r\n",                        /* Ustawienie obsługi wielu
                                             * połączeń */
  "AT+CIPSERVER=1,7\r\n",                   /* Włączenie serwera i 
                                             * ustawienie portu 7 */
  "AT+CWMODE=?\r\n",                        /* Sprawdzenie trybu 
                                             * pracy */
  "AT+CWJAP=\"marx\",\"************\"\r\n", /* Połączenie z siecią 
                                             * Wi-Fi */
  "AT+CIPSTA?\r\n",                         /* Sprawdzenie statusu 
                                             * połączenia z Wi-Fi */
  "AT+CIFSR\r\n"                            /* Wyświetlenie adresu 
                                             * IP serwera */
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

  /* Pętla konfiguracji modułu przesyłająca kolejne komendy konfiguracyjne */
  for(i = 0; i < COMMANDS; i++)
  {
    /* Przesłanie komendy konfiguracyjnej */
    HAL_UART_Transmit(&huart6, (uint8_t*)(config[i]), strlen(config[i]), 10);
    /* Wyczyszczenie bufora odbiorczego */
    clr_buffer(data_r, 1000);
    /* Odbiór komunikatu zwrotnego */
    HAL_UART_Receive(&huart6, (uint8_t*)data_r, sizeof(data_r), 100);

    /* Odczekanie sekundy po komendzie restartu modułu */
    if(i == 0)
    {
      HAL_Delay(1000);
    }

    /* Pętla oczekiwania na otrzymanie adresu z DHCP routera */
    while(is_busy())
    {
      /* Odczekanie sekundy */
        HAL_Delay(1000);
        /* Wysłanie komendy sprawdzającej status otrzymanego adresu IP,
         * maski oraz bramy */
      HAL_UART_Transmit(&huart6, (uint8_t*)(config[i]), strlen(config[i]), 
                        10);
      /* Wyczyszczenie buforu odbiorczego */
      clr_buffer(data_r, 1000);
      /* Otrzymanie komunikatu zwrotnego */
      HAL_UART_Receive(&huart6, (uint8_t*)data_r, sizeof(data_r), 
                       100);
    }
    /* Przesłanie komunikatu zwrotnego poprzez port szeregowy do 
     * komputera nadzorującego */
    HAL_UART_Transmit(&huart3, (unsigned char*)data_r, sizeof(data_r), 
                      10);
    HAL_UART_Transmit(&huart3, (unsigned char*)"\r\n\n", sizeof("\r\n\n"), 
                      10);

  }

  while (1)
  {
    /* USER CODE END WHILE */
    /* Wyczyszczenie bufora odbiorczego */
    clr_buffer(data_r, 1000);
    /* Pobór komunikatu z modułu */
    HAL_UART_Receive(&huart6, (uint8_t*)data_r, sizeof(data_r), 100);
    /* Jeżeli ustawiona jest flaga gotowości do wysłania wiadomości echo */
    if(ready_to_send)
    {
      /* Wysłanie wiadomości echo */
      HAL_UART_Transmit(&huart6, (uint8_t*)message, sizeof(message), 10);
      /* Reset flagi gotowości do wysłania wiadomości echo */
      ready_to_send = 0;
    }
    /* W przeciwnym wypadku, jeżeli otrzymany komunikat nie jest pustym
     * komunikatem */
    else if (data_r[0] != 0)
    {
      /* Przygotowanie do wysłania wiadomości echo */
      prepare_echo();
      /* Wysłanie otrzymanego komunikatu za pomocą portu szeregowego */
      HAL_UART_Transmit(&huart3, (unsigned char*)data_r, sizeof(data_r), 
                        10);
      HAL_UART_Transmit(&huart3, (unsigned char*)"\r\n\n", 
                        sizeof("\r\n\n"), 10);
    }

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}