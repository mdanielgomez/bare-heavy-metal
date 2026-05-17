#include "stm32f103.h"
#include "arm.h"

#define UART_RX_BUFFER_SIZE 64

void TIM2_IRQHandler()
{
    if (TIM2->SR & 1u)
    {
        TIM2->SR &= ~1u;
        GPIOA->ODR ^= (1 << 5);
    }
}

int main(void)
{
    // Enable TIM2 Peripheral
    RCC->APB1ENR |= 1 << 0;

    // Enable GPIOA, USART, and DMA Clock
    RCC->APB2ENR |= 1 << 2;
    RCC->APB1ENR |= 1 << 17;
    RCC->AHBENR |= 1 << 0;

    // Configure PA2 and PA3
    GPIOA->CRL &= ~(0b1111 << 8); // Reset GPIOA2
    GPIOA->CRL |= (0b1010 << 8); // AF Push Pull, Output mode max 2 MHz

    GPIOA->CRL &= ~(0b1111 << 12); // Reset GPIOA3
    GPIOA->CRL |= (0b0001 << 12); // Floating input mode

    // Set Baud
    USART2->BRR = (4 << 4) | 5;
    USART2->CR1 = 0;
    USART2->CR1 |= (1 << 3);
    USART2->CR1 |= (1 << 2);
    USART2->CR1 |= (1 << 13);

    volatile uint8_t uart_rx_buffer[64];

    // Set up DMA
    DMA1->CCR1 &= ~(1 << 0);
    DMA1->CPAR1 = &USART2->DR;
    DMA1->CMAR1 = uart_rx_buffer;
    DMA1->CNDTR1 = UART_RX_BUFFER_SIZE;

    DMA1->CCR1 = 0;
    DMA1->CCR1 |= (1 << 7);
    DMA1->CCR1 |= (1 << 5);

    // Enable DMA on USART2
    USART2->CR3 |= (1 << 6);

    // Enable DMA
    DMA1->CCR1 |= 1;

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
    GPIOA->CRL = 0x44444444;

    // Set PA5 configuration to open-drain
    // Set PA5 mode to output 2 MHz max
    GPIOA->CRL &= ~(0xF << 20);
    GPIOA->CRL |= 0b0010 << 20;

    // Turn on LED with timer
    while (1)
    {
    }
    return 0;
}
