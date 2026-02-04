#include "stm32f103_regs.h"

int main(void)
{
    // Enable GPIO A Peripheral Clock
    RCC->APB2ENR |= 1 << 2;

    // Configure GPIOA5
    // Reset PA5
    GPIOA->CRL &= 4 << 20;

    // Set PA5 configuration to open-drain
    GPIOA->CRL |= 1 << 20;

    // Set PA5 mode to output 2 MHz max
    GPIOA->CRL |= 2 << 22;

    // Turn on LED
    GPIOA->BRR |= 1 << 5;
}
