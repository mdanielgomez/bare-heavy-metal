#include "rcc.h"
#include "stm32f103.h"

void rcc_enable_gpioa(void)
{
    RCC->APB2ENR |= 1 << 2;
}
void rcc_enable_tim2(void)
{
    RCC->APB1ENR |= 1 << 0;
}
void rcc_enable_usart2(void)
{
    RCC->APB1ENR |= 1 << 17;
}