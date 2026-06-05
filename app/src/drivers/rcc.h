#pragma once

typedef enum
{
    RCC_APB1PRE_NOT_DIVIDED = 0b000,
    RCC_APB1PRE_DIV_2       = 0b100,
    RCC_APB1PRE_DIV_4       = 0b101,
    RCC_APB1PRE_DIV_8       = 0b110,
    RCC_APB1PRE_DIV_16      = 0b111
} rcc_apbpre_t;

typedef enum
{
    RCC_PLL_MULT_4 = 0b0010,
    RCC_PLL_MULT_5 = 0b0011,
    RCC_PLL_MULT_6 = 0b0100,
    RCC_PLL_MULT_7 = 0b0101,
    RCC_PLL_MULT_8 = 0b0110,
    RCC_PLL_MULT_9 = 0b0111
} rcc_pll_mult_t;

typedef enum
{
    SYSCLK_SET_HSI = 0b00,
    SYSCLK_SET_HSE = 0b01,
    SYSCLK_SET_PLL = 0b10
} sysclk_set_t;

void rcc_enable_gpioa(void);
void rcc_enable_tim2(void);
void rcc_enable_usart2(void);