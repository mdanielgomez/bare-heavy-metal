#include "uart.h"
#include "gpio.h"
#include "clock.h"

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

void uart_init(uart_handle_t* handle)
{
    if (handle->uart == USART1)
    {
        RCC->APB2ENR |= 1 << 14;
    }
    else
    {
        uint32_t base = ((uint32_t)handle->uart - USART2_BASE) / 0x400UL;
        RCC->APB1ENR |= 1 << (17 + base);
    }
    gpio_configure_pin(handle->tx_gpio, handle->tx_gpio_pin, GPIO_MODE_OUTPUT_2MHZ,
                       GPIO_CNF_OUTPUT_PUSH_PULL); // configure tx pin
    gpio_configure_pin(handle->rx_gpio, handle->rx_gpio_pin, GPIO_MODE_INPUT,
                       GPIO_CNF_INPUT_FLOATING); // configure rx pin

    // set baud
    handle->uart->BRR =
        (clock_get_pclk1_hz() + (handle->config.baud_rate / 2)) / handle->config.baud_rate;
}