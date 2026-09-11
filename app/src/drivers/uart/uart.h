#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "stm32f103.h"

#define UART_RX_BUFFER_SIZE 128u
#define UART_TX_BUFFER_SIZE 128u

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

typedef struct
{
    USART_TypeDef* uart;
    uart_config_t  config;

    GPIO_TypeDef* rx_gpio;
    uint8_t       rx_gpio_pin;

    GPIO_TypeDef* tx_gpio;
    uint8_t       tx_gpio_pin;

    uint8_t* rx_buffer;
    uint16_t rx_buffer_size;
    uint16_t rx_tail;

    uint8_t*          tx_buffer;
    uint16_t          tx_buffer_size;
    volatile uint16_t tx_head;
    volatile uint16_t tx_tail;
    volatile uint16_t tx_dma_length;
    uint8_t           dma_rx_channel;
    uint8_t           dma_tx_channel;
} uart_handle_t;

typedef void (*uart_rx_callback_t)(uint8_t byte, void* context);

void uart_set_baud_rate(USART_TypeDef* uart, uint32_t brr);
void uart_enable_transmit(USART_TypeDef* uart);
void uart_enable_receiver(USART_TypeDef* uart);
void uart_enable_uart(USART_TypeDef* uart);
void uart_enable_dma(USART_TypeDef* uart);

void uart_write_char(USART_TypeDef* uart, char c);
bool uart_write_byte(uart_handle_t* handle, uint8_t byte);
size_t uart_write(uart_handle_t* handle, const uint8_t* data, size_t length);
size_t uart_process_receive(uart_handle_t* handle, uart_rx_callback_t callback, void* context);
void uart_init(uart_handle_t* handle);
