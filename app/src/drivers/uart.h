#pragma once

#include "stm32f103.h"

typedef enum
{
    UART_STOP_1    = 0b00,
    UART_STOP_0PT5 = 0b01,
    UART_STOP_2    = 0b10,
    UART_STOP_1PT5 = 0b11
} uart_stop_t;

typedef enum
{
    UART_PARITY_NONE,
    UART_PARITY_EVEN,
    UART_PARITY_ODD
} uart_parity_t;

typedef enum
{
    UART_WORD_8,
    UART_WORD_9
} uart_word_t;

typedef enum
{
    UART_MODE_TX,
    UART_MODE_RX,
    UART_MODE_TX_RX
} uart_mode_t;

typedef struct
{
    uint32_t      baud_rate;
    uart_stop_t   stop_bits;
    uart_parity_t parity;
    uart_word_t   word_length;
    uart_mode_t   mode;
} uart_config_t;

void uart_set_baud_rate(USART_TypeDef* uart, uint32_t brr);
void uart_enable_transmit(USART_TypeDef* uart);
void uart_enable_receiver(USART_TypeDef* uart);
void uart_enable_uart(USART_TypeDef* uart);
void uart_enable_dma(USART_TypeDef* uart);

void uart_write_char(USART_TypeDef* uart, char c);
void uart_init(USART_TypeDef* uart, uart_config_t config);