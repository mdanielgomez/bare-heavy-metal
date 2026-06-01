#include "uart.h"

void uart_set_baud_rate(USART_TypeDef* uart, uint32_t brr)
{
    uart->BRR = brr;
}
void uart_enable_transmit(USART_TypeDef* uart)
{
    uart->CR1 |= 1 << 3;
}
void uart_enable_receiver(USART_TypeDef* uart)
{
    uart->CR1 |= 1 << 2;
}
void uart_enable_uart(USART_TypeDef* uart)
{
    uart->CR1 |= 1 << 13;
}
void uart_enable_dma(USART_TypeDef* uart)
{
    uart->CR3 |= 1 << 6;
}
void uart_write_char(USART_TypeDef* uart, char c)
{
    while (!(uart->SR & (1 << 7)))
    {
        // wait for TXE
    }

    uart->DR = c;
}
