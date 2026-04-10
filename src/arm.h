#define NVIC_BASE 0xE000E100

typedef struct
{
    volatile unsigned int ISER[8];
    volatile unsigned int reserved[24];
    volatile unsigned int ICER[8];
} NVIC_TypeDef;

#define NVIC ((NVIC_TypeDef*)NVIC_BASE)
