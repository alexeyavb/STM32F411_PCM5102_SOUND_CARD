#include "main.h"
#include "usbd_core.h"
#include "usb_config.h"

#ifdef UART_DEBUG_ENABLED
extern UART_HandleTypeDef huart1;
#endif
extern PCD_HandleTypeDef hpcd_USB_FS;

int fputc(int ch, FILE *f)
{
#ifdef UART_DEBUG_ENABLED
    while ((USART1->SR & USART_SR_TXE) == 0)
        ;
    USART1->DR = ch;
    return ch;
#endif
}

void usb_dc_low_level_init(void){
  /* Peripheral clock enable */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USB_OTG_FS GPIO Configuration
    PA8     ------> USB_OTG_FS_SOF
    PA11     ------> USB_OTG_FS_DM
    PA12     ------> USB_OTG_FS_DP
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USB_OTG_FS clock enable */
    if(__HAL_RCC_USB_OTG_FS_IS_CLK_DISABLED())
      __HAL_RCC_USB_OTG_FS_CLK_ENABLE();

    // __HAL_RCC_USB_OTG_FS_CLK_ENABLE();

    /* USB_OTG_FS interrupt Init */
    HAL_NVIC_SetPriority(OTG_FS_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(OTG_FS_IRQn);
}

void usb_rx_tx_test_for_main_loop(){
        extern void cdc_acm_data_send_with_dtr_test(uint8_t busid);
        cdc_acm_data_send_with_dtr_test(0);
        HAL_Delay(100);
}

/* export irq for usb otg fs ========================================*/
// void USB_LP_CAN1_RX0_IRQHandler(void)
// {
//   /* USER CODE BEGIN USB_LP_CAN1_RX0_IRQn 0 */
//   /* USER CODE END USB_LP_CAN1_RX0_IRQn 0 */
//   //HAL_PCD_IRQHandler(&hpcd_USB_FS);
//   /* USER CODE BEGIN USB_LP_CAN1_RX0_IRQn 1 */
//     extern void USBD_IRQHandler(uint8_t busid);
//     USBD_IRQHandler(0);
//   /* USER CODE END USB_LP_CAN1_RX0_IRQn 1 */
// }
