#include "stm32f103_regs.h"

int main(void)
{

    // Enable GPIO A Peripheral Clock
    RCC->APB2ENR |= 1 << 2;

    // Configure GPIOA5
    // Reset PA5
    GPIOA->CRL = 0x44444444;

    // Set PA5 configuration to open-drain
    // Set PA5 mode to output 2 MHz max
    GPIOA->CRL &= ~(0xF << 20);
    GPIOA->CRL |= 0b0010 << 20;

    // Turn on LED
    GPIOA->ODR = 1 << 5;
    return 0;
}
