#pragma once

#include "stm32f103.h"

void uart_set_baud_rate(USART_TypeDef* uart, uint32_t brr);
void uart_enable_transmit(USART_TypeDef* uart);
void uart_enable_receiver(USART_TypeDef* uart);
void uart_enable_uart(USART_TypeDef* uart);
void uart_enable_dma(USART_TypeDef* uart);

void uart_write_char(USART_TypeDef* uart, char c);
