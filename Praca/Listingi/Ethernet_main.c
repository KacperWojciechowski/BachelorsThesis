/* Struktura połączenia */
extern struct netif gnetif;
extern UART_HandleTypeDef huart3;

/* Bufory tekstowe na dane połączenia */
char conn_msg_str[24];  // wiadomość
char ip_str[24];        // adres IP
char mask_str[24];      // maska
char gw_str[24];        // brama
char mac_str[30];       // adres MAC

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration-------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the 
   * Systick. */
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
  MX_LWIP_Init();
  /* USER CODE BEGIN 2 */
  /* Przesłanie adresu MAC za pomocą portu szeregowego */
  send_MAC_address();
  /* Sprawdzenie stanu połączenia */
  notify_dhcp_status(&gnetif);
  /* Inicjalizacja serwera echo */
  init_echo();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* Przetworzenie danych przez stos LwIP */
    MX_LWIP_Process();
    /* Sprawdzenie stanu połączenia */
    notify_dhcp_status(&gnetif);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}