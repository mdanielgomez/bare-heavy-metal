#pragma once

#include <stdint.h>

#define RCC_BASE 0x40021000UL
#define GPIOA_BASE 0x40010800UL
#define TIM2_BASE 0x40000000UL
#define DMA1_BASE 0x40020000UL
#define USART2_BASE 0x40004400UL
#define FLASH_ACR_BASE 0x40022000UL

typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    volatile uint32_t AHBSTR;
    volatile uint32_t CFGR2;
} RCC_TypeDef;

typedef struct
{
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIO_TypeDef;

typedef struct
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMCR;
    volatile uint32_t DIER;
    volatile uint32_t SR;
    volatile uint32_t EGR;
    volatile uint32_t CCMR1;
    volatile uint32_t CCMR2;
    volatile uint32_t CCER;
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
    volatile uint32_t RES;
    volatile uint32_t CCR1;
    volatile uint32_t CCR2;
    volatile uint32_t CCR3;
    volatile uint32_t CCR4;
    volatile uint32_t RES2;
    volatile uint32_t DCR;
    volatile uint32_t DMAR;
} TIM2_TypeDef;

typedef struct
{
    volatile uint32_t ISR;
    volatile uint32_t IFCR;
    volatile uint32_t CCR1;
    volatile uint32_t CNDTR1;
    volatile uint32_t CPAR1;
    volatile uint32_t CMAR1;
    volatile uint32_t RES1;
    volatile uint32_t CCR2;
    volatile uint32_t CNDTR2;
    volatile uint32_t CPAR2;
    volatile uint32_t CMAR2;
    volatile uint32_t RES2;
    volatile uint32_t CCR3;
    volatile uint32_t CNDTR3;
    volatile uint32_t CPAR3;
    volatile uint32_t CMAR3;
    volatile uint32_t RES3;
    volatile uint32_t CCR4;
    volatile uint32_t CNDTR4;
    volatile uint32_t CPAR4;
    volatile uint32_t CMAR4;
    volatile uint32_t RES4;
    volatile uint32_t CCR5;
    volatile uint32_t CNDTR5;
    volatile uint32_t CPAR5;
    volatile uint32_t CMAR5;
    volatile uint32_t RES5;
    volatile uint32_t CCR6;
    volatile uint32_t CNDTR6;
    volatile uint32_t CPAR6;
    volatile uint32_t CMAR6;
    volatile uint32_t RES6;
    volatile uint32_t CCR7;
    volatile uint32_t CNDTR7;
    volatile uint32_t CPAR7;
    volatile uint32_t CMAR7;
    volatile uint32_t RES7;
} DMA1_TypeDef;

typedef struct
{
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_TypeDef;


#define RCC ((RCC_TypeDef*)RCC_BASE)
#define GPIOA ((GPIO_TypeDef*)GPIOA_BASE)
#define TIM2 ((TIM2_TypeDef*)TIM2_BASE)
#define DMA1 ((DMA1_TypeDef*)DMA1_BASE)
#define USART2 ((USART_TypeDef*)USART2_BASE)
#define FLASH_ACR (*(volatile uint32_t*)FLASH_ACR_BASE)
