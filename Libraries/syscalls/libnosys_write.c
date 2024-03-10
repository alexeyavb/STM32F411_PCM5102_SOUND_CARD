#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
// Буфер для кеширования обращений к uart.
// static const uint32_t m_uart_buf_size = 254;
// static uint8_t m_uart_tx_buf[m_uart_buf_size] = {0};
static uint32_t buf_p = 0;
int fputc(int ch, FILE *f)
{
    while ((USART1->SR & USART_SR_TXE) == 0);
    USART1->DR = ch;
    return ch;
}

int uart1_fputc(int ch)
{
    while ((USART1->SR & USART_SR_TXE) == 0);
    USART1->DR = ch;
    return ch;
}

int uart_putc( const char ch)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    {}
    USART_SendData(USART1, (uint8_t) ch);
return 0;
}
int _write_r (struct _reent *r, int file, char * ptr, int len)
{  
  r = r;
  file = file;
  ptr = ptr;
#if 0
  int index;
  /* For example, output string by UART */
  for(index=0; index<len; index++)
  {
    if (ptr[index] == '\n')
    {
      uart1_putc('\r');
    }  
    uart1_putc(ptr[index]);
  }  
#endif   
  return len;
}
int _write_old_r (struct _reent *r, int file, char * ptr, int len)
{  
  r = r;
  file = file;
  ptr = ptr;
#if 0
  int index;
  /* For example, output string by UART */
  for(index=0; index<len; index++)
  {
    if (ptr[index] == '\n')
    {
      uart_putc('\r');
    }  
    uart_putc(ptr[index]);
  }  
#endif   
  return len;
}