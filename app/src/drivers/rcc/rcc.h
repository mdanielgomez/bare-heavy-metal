#pragma once

#define RCC_CFGR_SW_POS 0
#define RCC_CFGR_SW_MASK 0b11 << RCC_CFGR_SW_POS
#define RCC_CFGR_SWS_POS 2
#define RCC_CFGR_SWS_MASK 0b11 << RCC_CFGR_SWS_POS

#define RCC_PLL_ENTRY_POS 16u
#define RCC_PLL_ENTRY_MASK 1u << RCC_PLL_ENTRY_POS
#define RCC_PLL_MULT_POS 18u
#define RCC_PLL_MULT_MASK 0b1111u << RCC_PLL_MULT_POS

#define RCC_CFGR_HPRE_POS 4u
#define RCC_CFGR_HPRE_MASK 0b1111 << RCC_CFGR_HPRE_POS
#define RCC_CFGR_PPRE1_POS 8u
#define RCC_CFGR_PPRE1_MASK 0b111 << RCC_CFGR_PPRE1_POS
#define RCC_CFGR_PPRE2_POS 11u
#define RCC_CFGR_PPRE2_MASK 0b111 << RCC_CFGR_PPRE2_POS

typedef enum
{
    RCC_PLL_ENTRY_HSI = 0,
    RCC_PLL_PREDIV1   = 1
} rcc_pll_entry_t;

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
    RCC_PLL_MULT_2  = 0b0000,
    RCC_PLL_MULT_3  = 0b0001,
    RCC_PLL_MULT_4  = 0b0010,
    RCC_PLL_MULT_5  = 0b0011,
    RCC_PLL_MULT_6  = 0b0100,
    RCC_PLL_MULT_7  = 0b0101,
    RCC_PLL_MULT_8  = 0b0110,
    RCC_PLL_MULT_9  = 0b0111,
    RCC_PLL_MULT_10 = 0b1000,
    RCC_PLL_MULT_11 = 0b1001,
    RCC_PLL_MULT_12 = 0b1010,
    RCC_PLL_MULT_13 = 0b1011,
    RCC_PLL_MULT_14 = 0b1100,
    RCC_PLL_MULT_15 = 0b1101,
    RCC_PLL_MULT_16 = 0b1110
} rcc_pll_mult_t;

typedef enum
{
    RCC_HPRE_NO_DIV  = 0b0000,
    RCC_HPRE_DIV_2   = 0b1000,
    RCC_HPRE_DIV_4   = 0b1001,
    RCC_HPRE_DIV_8   = 0b1010,
    RCC_HPRE_DIV_16  = 0b1011,
    RCC_HPRE_DIV_64  = 0b1100,
    RCC_HPRE_DIV_128 = 0b1101,
    RCC_HPRE_DIV_256 = 0b1110,
    RCC_HPRE_DIV_512 = 0b1111
} rcc_hpre_prescalar_t;

typedef enum
{
    RCC_PPRE_NO_DIV = 0b000,
    RCC_PPRE_DIV_2  = 0b100,
    RCC_PPRE_DIV_4  = 0b101,
    RCC_PPRE_DIV_8  = 0b110,
    RCC_PPRE_DIV_16 = 0b111
} rcc_ppre_t;

typedef enum
{
    SYSCLK_SET_HSI = 0b00,
    SYSCLK_SET_HSE = 0b01,
    SYSCLK_SET_PLL = 0b10
} rcc_sysclk_set_t;

void rcc_enable_gpioa(void);
void rcc_enable_tim2(void);
void rcc_enable_usart2(void);
