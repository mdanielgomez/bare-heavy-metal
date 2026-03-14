#include "stm32f103_regs.h"

int main(void)
{
    // Enable TIM2 Peripheral
    RCC->APB1ENR |= 1 << 0;

    // Disable the timer
    TIM2->CR1 &= ~1;

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
        while ((TIM2->SR & 1u) == 0)
        {
        }
        TIM2->SR &= ~1u;
        GPIOA->ODR ^= (1 << 5);
    }
    return 0;
}
