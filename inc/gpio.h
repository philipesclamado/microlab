#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
  GPIO_OK = 0,
  GPIO_ERROR_INVALID_PIN,
  GPIO_ERROR_INVALID_CONFIG,
} GPIO_Status;

typedef enum {
  GPIO_MODE_INPUT = 0U,
  GPIO_MODE_OUTPUT = 1U,
} GPIO_Mode;

typedef enum {
  GPIO_OUTPUT_TYPE_PUSHPULL = 0U,
  GPIO_OUTPUT_TYPE_OPENDRAIN = 1U,
} GPIO_OutputType;

typedef enum {
  GPIO_SPEED_LOW = 0U,
  GPIO_SPEED_HIGH = 3U,
} GPIO_OutputSpeed;

typedef enum {
  GPIO_PULL_NONE = 0U,
  GPIO_PULL_UP = 1U,
  GPIO_PULL_DOWN = 2U,
} GPIO_Pull;

typedef struct {
  volatile uint32_t MODER;
  volatile uint32_t OTYPER;
  volatile uint32_t OSPEEDR;
  volatile uint32_t PUPDR;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t LCKR;
  volatile uint32_t AFRL;
  volatile uint32_t AFRH;
} GPIO_TypeDef;

typedef enum { GPIO_LOW = 0U, GPIO_HIGH = 1U } GPIO_Level;

// ref.
// https://www.st.com/resource/en/reference_manual/rm0091-stm32f0x1stm32f0x2stm32f0x8-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
#define GPIOA ((GPIO_TypeDef *)0x48000000UL)
#define GPIOB ((GPIO_TypeDef *)0x48000400UL)
#define GPIOC ((GPIO_TypeDef *)0x48000800UL)

#define RCC_AHBENR (*(volatile uint32_t *)(0x40021014UL))

GPIO_Status GPIO_Init(GPIO_TypeDef *port, uint8_t pin, uint8_t mode,
                      uint8_t output_type, uint8_t output_speed,
                      uint8_t pull_up_down);

GPIO_Status GPIO_Write(GPIO_TypeDef *port, uint8_t pin, GPIO_Level level);

GPIO_Level GPIO_Read(GPIO_TypeDef *port, uint8_t pin);

#endif
