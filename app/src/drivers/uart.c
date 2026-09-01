#include "uart.h"
#include "gpio.h"
#include "clock.h"
#include "dma.h"
#include "arm.h"

#define USART_CR3_DMAR (1u << 6)
#define USART_CR3_DMAT (1u << 7)

static uart_handle_t* tx_dma_handles[8];

static void uart_start_tx_dma(uart_handle_t* handle)
{
    uint16_t length;

    if (handle->tx_dma_length != 0u || handle->tx_head == handle->tx_tail)
    {
        return;
    }

    if (handle->tx_head > handle->tx_tail)
    {
        length = handle->tx_head - handle->tx_tail;
    }
    else
    {
        length = handle->tx_buffer_size - handle->tx_tail;
    }

    handle->tx_dma_length = length;
    dma_channel_clear_flags(DMA1, handle->dma_tx_channel);

    const dma_channel_config_t config = {
        .dma                         = DMA1,
        .peripheral_address          = (uintptr_t)&handle->uart->DR,
        .buffer                      = (uintptr_t)&handle->tx_buffer[handle->tx_tail],
        .buffer_size                 = length,
        .channel                     = handle->dma_tx_channel,
        .memory_inc_mode             = DMA_MINC_ENABLED,
        .peripheral_inc_mode         = DMA_PINC_DISABLED,
        .circular_inc_mode           = DMA_CIRC_DISABLE,
        .direction                   = DMA_DIRECTION_MEMORY_TO_PERIPHERAL,
        .transfer_complete_interrupt = 1u,
    };
    dma_config_channel(&config);
    dma_channel_enable(DMA1, handle->dma_tx_channel);
}

static void uart_handle_tx_dma_interrupt(uint8_t channel)
{
    uart_handle_t* handle = tx_dma_handles[channel];

    if (handle == NULL || !dma_channel_transfer_complete(DMA1, channel))
    {
        return;
    }

    dma_channel_disable(DMA1, channel);
    dma_channel_clear_flags(DMA1, channel);
    handle->tx_tail = (handle->tx_tail + handle->tx_dma_length) % handle->tx_buffer_size;
    handle->tx_dma_length = 0u;
    uart_start_tx_dma(handle);
}

void DMA1_Channel2_IRQHandler(void)
{
    uart_handle_tx_dma_interrupt(2u);
}

void DMA1_Channel4_IRQHandler(void)
{
    uart_handle_tx_dma_interrupt(4u);
}

void DMA1_Channel7_IRQHandler(void)
{
    uart_handle_tx_dma_interrupt(7u);
}

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

bool uart_write_byte(uart_handle_t* handle, uint8_t byte)
{
    uint16_t next_head;

    if (handle == NULL || handle->tx_buffer == NULL || handle->tx_buffer_size < 2u)
    {
        return false;
    }

    next_head = (handle->tx_head + 1u) % handle->tx_buffer_size;
    if (next_head == handle->tx_tail)
    {
        return false;
    }

    handle->tx_buffer[handle->tx_head] = byte;
    handle->tx_head = next_head;
    uart_start_tx_dma(handle);
    return true;
}

size_t uart_write(uart_handle_t* handle, const uint8_t* data, size_t length)
{
    size_t written = 0u;

    if (data == NULL)
    {
        return 0u;
    }

    while (written < length && uart_write_byte(handle, data[written]))
    {
        written++;
    }

    return written;
}

size_t uart_process_receive(uart_handle_t* handle, uart_rx_callback_t callback, void* context)
{
    size_t processed = 0u;
    uint16_t rx_head;

    if (handle == NULL || callback == NULL || handle->rx_buffer == NULL ||
        handle->rx_buffer_size == 0u)
    {
        return 0u;
    }

    rx_head = handle->rx_buffer_size -
              dma_channel_get_remaining(DMA1, handle->dma_rx_channel);

    while (handle->rx_tail != rx_head)
    {
        callback(handle->rx_buffer[handle->rx_tail], context);
        handle->rx_tail = (handle->rx_tail + 1u) % handle->rx_buffer_size;
        processed++;
    }

    return processed;
}

void uart_init(uart_handle_t* handle)
{
    if (handle == NULL || handle->config.baud_rate == 0u)
    {
        return;
    }

    if (handle->uart == USART1)
    {
        RCC->APB2ENR |= 1 << 14;
    }
    else
    {
        uint32_t base = ((uint32_t)handle->uart - USART2_BASE) / 0x400UL;
        RCC->APB1ENR |= 1 << (17 + base);
    }
    if (handle->config.mode != UART_MODE_RX)
    {
        gpio_configure_pin(handle->tx_gpio, handle->tx_gpio_pin, GPIO_MODE_OUTPUT_2MHZ,
                           GPIO_CNF_OUTPUT_AF_PUSH_PULL);
    }
    if (handle->config.mode != UART_MODE_TX)
    {
        gpio_configure_pin(handle->rx_gpio, handle->rx_gpio_pin, GPIO_MODE_INPUT,
                           GPIO_CNF_INPUT_FLOATING);
    }

    // set baud
    uint32_t pclk;

    if (handle->uart == USART1)
    {
        pclk = clock_get_pclk2_hz();
    }
    else
    {
        pclk = clock_get_pclk1_hz();
    }
    handle->uart->BRR = (pclk + (handle->config.baud_rate / 2)) / handle->config.baud_rate;

    handle->uart->CR1 &= ~((1u << 13) | (1u << 12) | (1u << 10) | (1u << 9) |
                           (1u << 3) | (1u << 2));
    handle->uart->CR2 &= ~(3u << 12);
    handle->uart->CR2 |= (uint32_t)handle->config.stop_bits << 12;

    if (handle->config.word_length == UART_WORD_9)
    {
        handle->uart->CR1 |= 1u << 12;
    }
    if (handle->config.parity != UART_PARITY_NONE)
    {
        handle->uart->CR1 |= 1u << 10;
        if (handle->config.parity == UART_PARITY_ODD)
        {
            handle->uart->CR1 |= 1u << 9;
        }
    }
    if (handle->config.mode != UART_MODE_RX)
    {
        handle->uart->CR1 |= 1u << 3;
    }
    if (handle->config.mode != UART_MODE_TX)
    {
        handle->uart->CR1 |= 1u << 2;
    }

    // set up dma
    if (handle->uart == USART1)
    {
        handle->dma_rx_channel = 5u;
        handle->dma_tx_channel = 4u;
    }
    else if (handle->uart == USART2)
    {
        handle->dma_rx_channel = 6u;
        handle->dma_tx_channel = 7u;
    }
    else if (handle->uart == USART3)
    {
        handle->dma_rx_channel = 3u;
        handle->dma_tx_channel = 2u;
    }
    else
    {
        // invalid UART
        return;
    }

    RCC->AHBENR |= 1u;
    handle->rx_tail = 0u;
    handle->tx_head = 0u;
    handle->tx_tail = 0u;
    handle->tx_dma_length = 0u;

    if (handle->config.mode != UART_MODE_TX && handle->rx_buffer != NULL &&
        handle->rx_buffer_size != 0u)
    {
        const dma_channel_config_t rx_config = {
            .dma                         = DMA1,
            .peripheral_address          = (uintptr_t)&handle->uart->DR,
            .buffer                      = (uintptr_t)handle->rx_buffer,
            .buffer_size                 = handle->rx_buffer_size,
            .channel                     = handle->dma_rx_channel,
            .memory_inc_mode             = DMA_MINC_ENABLED,
            .peripheral_inc_mode         = DMA_PINC_DISABLED,
            .circular_inc_mode           = DMA_CIRC_ENABLED,
            .direction                   = DMA_DIRECTION_PERIPHERAL_TO_MEMORY,
            .transfer_complete_interrupt = 0u,
        };
        dma_config_channel(&rx_config);
        dma_channel_clear_flags(DMA1, handle->dma_rx_channel);
        dma_channel_enable(DMA1, handle->dma_rx_channel);
        handle->uart->CR3 |= USART_CR3_DMAR;
    }

    if (handle->config.mode != UART_MODE_RX && handle->tx_buffer != NULL &&
        handle->tx_buffer_size >= 2u)
    {
        tx_dma_handles[handle->dma_tx_channel] = handle;
        handle->uart->CR3 |= USART_CR3_DMAT;
        NVIC->ISER[0] = 1u << (10u + handle->dma_tx_channel);
    }

    handle->uart->CR1 |= 1u << 13;
}
