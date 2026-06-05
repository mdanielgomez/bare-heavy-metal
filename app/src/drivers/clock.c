#include "clock.h"
#include "stm32f103.h"
#include "rcc.h"

void clock_init_72mhz(void)
{
    // Set hclock to 72MHz, APB1 clock to 36 MHz
    // Enable HSE. 8 Mhz is default
    RCC->CR |= 1 << 16;
    while (!(RCC->CR & (1 << 17)))
    {
    }

    FLASH_ACR &= ~0b111;               // clear flash latency bits
    FLASH_ACR |= FLASH_LATENCY_2 << 0; // set flash access latency to 2 wait cycles
    FLASH_ACR |= 1 << 4;               // enable prefetch buffer

    RCC->CFGR &= ~((0xF << 4) | (0x7 << 8) | (0x7 << 11) | (1 << 16) |
                   (0xF << 18));           // clear bits, set ahb prescalr to no division
    RCC->CFGR |= (RCC_APB1PRE_DIV_2 << 8); // set low speed prescalar to /2
    RCC->CFGR |= (1 << 16);                // set hse as pll source
    RCC->CFGR |= (RCC_PLL_MULT_9 << RCC_PLL_MULT_POS); // set pll multiplication to x9
    RCC->CR |= (1 << 24);                              // enable PLL
    while (!(RCC->CR & (1 << 25)))
    {
    } // wait PLLRDY

    RCC->CFGR &= ~(RCC_CFGR_SW_MASK);   // clear bits
    RCC->CFGR |= (SYSCLK_SET_PLL << 0); // set PLL as source for sysclock

    while (((RCC->CFGR >> 2) & 0b11) != 0b10)
    {
    } // wait for sysclock to be ready
}

uint32_t clock_get_sysclk_hz(void)
{
    switch (RCC->CFGR)
}