#include "stm32f103.h"
#include "arm.h"
#include "clock.h"
#include "uart.h"

void TIM2_IRQHandler()
{
    if (TIM2->SR & 1u)
    {
        TIM2->SR &= ~1u;
        GPIOA->ODR ^= (1 << 5);
    }
}

static uint8_t uart_rx_buffer[UART_RX_BUFFER_SIZE];
static uint8_t uart_tx_buffer[UART_TX_BUFFER_SIZE];

static uart_handle_t uart2 = {
    .uart = USART2,
    .config = {
        .baud_rate  = 9600u,
        .stop_bits  = UART_STOP_1,
        .parity     = UART_PARITY_NONE,
        .word_length = UART_WORD_8,
        .mode       = UART_MODE_TX_RX,
    },
    .rx_gpio       = GPIOA,
    .rx_gpio_pin   = 3u,
    .tx_gpio       = GPIOA,
    .tx_gpio_pin   = 2u,
    .rx_buffer     = uart_rx_buffer,
    .rx_buffer_size = sizeof(uart_rx_buffer),
    .tx_buffer     = uart_tx_buffer,
    .tx_buffer_size = sizeof(uart_tx_buffer),
};

static void echo_received_byte(uint8_t byte, void* context)
{
    (void)uart_write_byte((uart_handle_t*)context, byte);
}

int main(void)
{
    clock_init_72mhz();
    // Enable TIM2 Peripheral
    RCC->APB1ENR |= 1 << 0;

    // Enable GPIOA clock; uart_init enables USART and DMA clocks.
    RCC->APB2ENR |= 1 << 2;
    uart_init(&uart2);

    // Disable the timer
    TIM2->CR1 &= ~1;

    // Enable the interrupt
    TIM2->DIER |= 1;
    NVIC->ISER[0] |= 1 << 28;

    // Set the prescalar and auto reload
    TIM2->PSC = 8000u - 1u; // 8MHz / 8000 = 1 kHz (1 ms per tick)
    TIM2->ARR = 500u - 1u;  // 500 ms per toggle -> 1 Hz blink
    TIM2->EGR = 1u;
    TIM2->SR  = 0u;

    // Enable the timer
    TIM2->CR1 |= 1;

    // Enable GPIO A Peripheral Clock
    RCC->APB2ENR |= 1 << 2;

    // Enable the clock for TIM2
    RCC->APB1ENR |= 1;

    // Configure GPIOA5
    // Reset PA5
    // GPIOA->CRL = 0x44444444;

    // Set PA5 configuration to open-drain
    // Set PA5 mode to output 2 MHz max
    GPIOA->CRL &= ~(0xF << 20);
    GPIOA->CRL |= 0b0010 << 20;

    // Turn on LED with timer
    while (1)
    {
        uart_process_receive(&uart2, echo_received_byte, &uart2);
    }
    return 0;
}
