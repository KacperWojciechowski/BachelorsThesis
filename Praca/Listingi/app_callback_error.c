/* Funkcja zwrotna błędu */
static void app_callback_error(void* arg, err_t err)
{
  /* Wskaźnik na strukturę echo_info */
  struct echo_info* info;
  /* Uciszenie ostrzeżeń */
  (void)err;

  /* Przypisanie zrzutowanego wskaźnika na strukturę */
  info = (struct echo_info*) arg;
  /* Jeżeli zapisano strukturę echo_info */
  if (info != NULL)
  {
    /* Zwolnienie zaalokowanej pamięci */
    mem_free(info);
  }
  /* Włączenie niebieskiej diody LED jako sygnalizację błędu */
  HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
}