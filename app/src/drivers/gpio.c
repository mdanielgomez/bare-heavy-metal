#include "gpio.h"

void gpio_configure_pin(GPIO_TypeDef* gpio, uint8_t pin, gpio_mode_t mode, gpio_cnf_t cnf){
  volatile uint32_t* config_register;
  uint8_t pin_offset = 4 * pin;
  if (pin < 8) {
    config_register = &gpio->CRL;
    pin_offset = pin * 4;
  }
  else {
    config_register = &gpio->CRH;
    pin_offset = (pin - 8) * 4
  }    

  uint32_t register_setting = ((cnf << 2) | mode) << pin_offset;
  *config_register |= register_setting;

}

void gpio_write_pin(GPIO_TypeDef* gpio, uint8_t pin, uint8_t value) {
  if (value) {
    gpio->BSRR |= 1 << pin;
  }
  else {
    gpio->BSRR |= 1 << (pin + 16);
  }
}

uint8_t gpio_read_pin(GPIO_TypeDef* gpio, uint8_t pin) {
  return (gpio->IDR >> pin) & 1;
}

void gpio_toggle_pin(GPIO_TypeDef* gpio, uint8_t pin){
  gpio->ODR ^= (1 << pin);
}