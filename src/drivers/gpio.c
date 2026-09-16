#include "gpio.h"
#include <stdint.h>

GPIO_Status GPIO_Init(GPIO_TypeDef *port, uint8_t pin, uint8_t mode,
                      uint8_t output_type, uint8_t output_speed,
                      uint8_t pull_up_down) {
  if (pin >= 16U) {
    return GPIO_ERROR_INVALID_PIN;
  }

  uint32_t shift = pin * 2U;

  port->MODER &= ~(3U << shift);
  port->MODER |= ((uint32_t)mode << shift);

  port->OTYPER &= ~(1UL << pin);
  port->OTYPER |= ((uint32_t)output_type << pin);

  port->OSPEEDR &= ~(3U << shift);
  port->OSPEEDR |= ((uint32_t)output_speed << shift);

  port->PUPDR &= ~(3U << shift);
  port->PUPDR |= ((uint32_t)pull_up_down << shift);

  return GPIO_OK;
}

GPIO_Status GPIO_Write(GPIO_TypeDef *port, uint8_t pin, GPIO_Level level) {
  if (pin >= 16U) {
    return GPIO_ERROR_INVALID_PIN;
  }

  if (level == GPIO_HIGH) {
    port->ODR |= (1UL << pin);
  } else {
    port->ODR &= ~(1UL << pin);
  }

  return GPIO_OK;
}

GPIO_Level GPIO_Read(GPIO_TypeDef *port, uint8_t pin) {
  if (pin >= 16U) {
    return GPIO_LOW;
  }

  if (port->IDR & (1UL << pin)) {
    return GPIO_HIGH;
  }

  return GPIO_LOW;
}
