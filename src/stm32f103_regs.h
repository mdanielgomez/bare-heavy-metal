#define RCC_BASE 0x40021000UL
#define GPIOA_BASE 0x40010800UL
#define TIM2_BASE 0x40000000UL

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
    volatile unsigned int CCMR1O;
    volatile unsigned int CCNR1I;
    volatile unsigned int CCMR2O;
    volatile unsigned int CCMR2I;
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

#define RCC ((RCC_TypeDef*)RCC_BASE)
#define GPIOA ((GPIO_TypeDef*)GPIOA_BASE)
#define TIM2 ((TIM2_TypeDef*)TIM2_BASE)
