#ifndef GPIO_H
#define GPIO_H

#include "stm32f103.h"

typedef enum {
  GPIO_MODE_INPUT = 0,
  GPIO_MODE_OUTPUT_2MHZ = 2,
  GPIO_MODE_OUTPUT_10MHZ = 1,
  GPIO_MODE_OUTPUT_50MHZ = 3
} gpio_mode_t;

typedef enum {
  GPIO_CNF_OUTPUT_PUSH_PULL = 0,
  GPIO_CNF_OUTPUT_OPEN_DRAIN = 1,
  GPIO_CNF_OUTPUT_AF_PUSH_PULL = 2,
  GPIO_CNF_OUTPUT_AF_OPEN_DRAIN = 3,

  GPIO_CNF_INPUT_ANALOG = 0,
  GPIO_CNF_INPUT_FLOATING = 1,
  GPIO_CNF_INPUT_PULL = 2
} gpio_cnf_t;

void gpio_configure_pin(GPIO_TypeDef* gpio, uint8_t pin, gpio_mode_t mode, gpio_cnf_t cnf);
void gpio_write_pin(GPIO_TypeDef* gpio, uint8_t pin, uint8_t value);
uint8_t gpio_read_pin(GPIO_TypeDef* gpio, uint8_t pin);
void gpio_toggle_pin(GPIO_TypeDef* gpio, uint8_t pin);

#endif