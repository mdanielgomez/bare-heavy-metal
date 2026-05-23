#ifndef GPIO_H
#define GPIO_H

#include "stm32f103.h"

typedef enum {
  GPIO_MODE_INPUT = 0,
  GPIO_MODE_OUTPUT_2MHZ = 2,
  GPIO_MODE_OUTPUT_10MHZ = 1,
  GPIO_MODE_OUTPUT_50MHZ = 3
} gpi_mode_t;

#endif