/* Connection structure */
extern struct netif gnetif;
extern UART_HandleTypeDef huart3;

/* Char buffer for connection data */
char conn_msg_str[24];  // message
char ip_str[24];        // IP address
char mask_str[24];      // mask
char gw_str[24];        // gateway
char mac_str[30];       // MAC address

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
  /* Sending MAC via serial port */
  send_MAC_address();
  /* Check connection status */
  notify_dhcp_status(&gnetif);
  /* Initialize echo server */
  init_echo();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* Process data via LwIP stack */
    MX_LWIP_Process();
    /* Check connection status */
    notify_dhcp_status(&gnetif);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}