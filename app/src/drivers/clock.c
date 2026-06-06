#include "clock.h"
#include "stm32f103.h"
#include "rcc.h"

static const uint32_t HSI_FREQ_HZ = 8000000;
static const uint32_t HSE_FREQ_HZ = 8000000; // from nucleo board.

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

static uint32_t clock_get_pll_output_hz()
{
    uint32_t pll_entry_freq;
    if ((RCC->CFGR & RCC_PLL_ENTRY_MASK) >> RCC_PLL_ENTRY_POS)
    {
        pll_entry_freq = HSE_FREQ_HZ;
    }
    else
    {
        pll_entry_freq = HSI_FREQ_HZ / 2; // clk freq is hsi/2
    }
    return pll_entry_freq *
           ((RCC->CFGR & RCC_PLL_MULT_MASK) + 2); // scale pll entry to get pll output
}
uint32_t clock_get_sysclk_hz(void)
{
    uint32_t sys_clk_freq;
    switch ((RCC->CFGR & RCC_CFGR_SWS_MASK) >> RCC_CFGR_SWS_POS)
    {
    case SYSCLK_SET_HSI:
        return HSI_FREQ_HZ;
        break;
    case SYSCLK_SET_HSE:
        return HSE_FREQ_HZ;
        break;
    case SYSCLK_SET_PLL:
        return clock_get_pll_output_hz();
    }
}
uint32_t clock_get_hclk_hz(void)
{
    uint32_t sysclk = clock_get_sysclk_hz();
    uint32_t hpre   = ((RCC->CFGR & RCC_CFGR_HPRE_MASK) >> RCC_CFGR_HPRE_POS);
    if (hpre < 8u)
    {
        return sysclk; // no division
    }
    uint32_t exponent = hpre - 7u;
    if (hpre >= 12)
    {
        exponent++; // adjust for prescaler skipping 32 as a value
    }
    uint32_t prescaler = 1u << exponent;
    return sysclk / prescaler;
}
uint32_t clock_get_pclk1_hz()
{
    uint32_t hclk = clock_get_hclk_hz();
    uint32_t ppre = (RCC->CFGR & RCC_CFGR_PPRE1_MASK) >> RCC_CFGR_PPRE1_POS;
    if (ppre < 4u)
    {
        return hclk; // no division
    }
    uint32_t exponent  = ppre - 3;
    uint32_t prescaler = 1u << exponent;
    return hclk / prescaler;
}
