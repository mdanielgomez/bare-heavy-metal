#pragma once

#include <stdint.h>

#define NVIC_BASE 0xE000E100
#define VTOR_REG 0xE000ED08

typedef struct
{
    volatile uint32_t ISER[8];
    volatile uint32_t reserved[24];
    volatile uint32_t ICER[8];
} NVIC_TypeDef;

#define NVIC ((NVIC_TypeDef*)NVIC_BASE)
#define VTOR (*(volatile unsigned int*)VTOR_REG)
