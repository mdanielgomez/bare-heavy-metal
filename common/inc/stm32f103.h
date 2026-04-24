#define RCC_BASE 0x40021000UL
#define GPIOA_BASE 0x40010800UL
#define TIM2_BASE 0x40000000UL
#define DMA_BASE 0x40020000UL

typedef struct
{
    volatile unsigned int CR;
    volatile unsigned int CFGR;
    volatile unsigned int CIR;
    volatile unsigned int APB2RSTR;
    volatile unsigned int APB1RSTR;
    volatile unsigned int AHBENR;
    volatile unsigned int APB2ENR;
    volatile unsigned int APB1ENR;
    volatile unsigned int BDCR;
    volatile unsigned int CSR;
    volatile unsigned int AHBSTR;
    volatile unsigned int CFGR2;
} RCC_TypeDef;

typedef struct
{
    volatile unsigned int CRL;
    volatile unsigned int CRH;
    volatile unsigned int IDR;
    volatile unsigned int ODR;
    volatile unsigned int BSRR;
    volatile unsigned int BRR;
    volatile unsigned int LCKR;
} GPIO_TypeDef;

typedef struct
{
    volatile unsigned int CR1;
    volatile unsigned int CR2;
    volatile unsigned int SMCR;
    volatile unsigned int DIER;
    volatile unsigned int SR;
    volatile unsigned int EGR;
    volatile unsigned int CCMR1;
    volatile unsigned int CCMR2;
    volatile unsigned int CCER;
    volatile unsigned int CNT;
    volatile unsigned int PSC;
    volatile unsigned int ARR;
    volatile unsigned int RES;
    volatile unsigned int CCR1;
    volatile unsigned int CCR2;
    volatile unsigned int CCR3;
    volatile unsigned int CCR4;
    volatile unsigned int RES2;
    volatile unsigned int DCR;
    volatile unsigned int DMAR;
} TIM2_TypeDef;

typedef struct
{
    volatile unsigned int ISR;
    volatile unsigned int IFCR;
    volatile unsigned int CCR1;
    volatile unsigned int CNDTR1;
    volatile unsigned int CPAR1;
    volatile unsigned int CMAR1;
    volatile unsigned int RES1;
    volatile unsigned int CCR2;
    volatile unsigned int CNDTR2;
    volatile unsigned int CPAR2;
    volatile unsigned int CMAR2;
    volatile unsigned int RES2;
    volatile unsigned int CCR3;
    volatile unsigned int CNDTR3;
    volatile unsigned int CPAR3;
    volatile unsigned int CMAR3;
    volatile unsigned int RES3;
    volatile unsigned int CCR4;
    volatile unsigned int CNDTR4;
    volatile unsigned int CPAR4;
    volatile unsigned int CMAR4;
    volatile unsigned int RES4;
    volatile unsigned int CCR5;
    volatile unsigned int CNDTR5;
    volatile unsigned int CPAR5;
    volatile unsigned int CMAR5;
    volatile unsigned int RES5;
    volatile unsigned int CCR6;
    volatile unsigned int CNDTR6;
    volatile unsigned int CPAR6;
    volatile unsigned int CMAR6;
    volatile unsigned int RES6;
    volatile unsigned int CCR7;
    volatile unsigned int CNDTR7;
    volatile unsigned int CPAR7;
    volatile unsigned int CMAR7;
    volatile unsigned int RES7;

} DMA_TypeDef;

#define RCC ((RCC_TypeDef*)RCC_BASE)
#define GPIOA ((GPIO_TypeDef*)GPIOA_BASE)
#define TIM2 ((TIM2_TypeDef*)TIM2_BASE)
#define DMA ((DMA_TypeDef*)DMA_BASE)
