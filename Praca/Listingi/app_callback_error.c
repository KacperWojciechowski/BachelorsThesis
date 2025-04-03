/* Error callback */
static void app_callback_error(void* arg, err_t err)
{
  /* echo_info pointer */
  struct echo_info* info;
  /* Silence warnings */
  (void)err;

  /* Downcasting the echo_info pointer from the parameter */
  info = (struct echo_info*) arg;
  /* If the echo_info pointer was properly downcasted */
  if (info != NULL)
  {
    /* Release allocated memory */
    mem_free(info);
  }
  /* Turn on the blue LED to signalize error */
  HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
}