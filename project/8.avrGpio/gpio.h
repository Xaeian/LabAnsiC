#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

#define GPIOB 0x03 + __SFR_OFFSET
#define GPIOC 0x06 + __SFR_OFFSET
#define GPIOD 0x09 + __SFR_OFFSET

#define GPIO_PIN(x) (*(volatile uint8_t *)(x))
#define GPIO_DDR(x) (*(volatile uint8_t *)(x + 1))
#define GPIO_PORT(x) (*(volatile uint8_t *)(x + 2))

typedef enum {
  GPIO_MODE_Input = 0,
  GPIO_MODE_Output = 1,
} GPIO_Mode_e;

typedef struct {
  uint8_t pin;
  GPIO_Mode_e mode;
  bool invert;
  bool pullup;
  bool set;
  uint8_t _gpio;
  uint8_t _pin;
} GPIO_t;

void GPIO_Set(GPIO_t *gpio);
void GPIO_Rst(GPIO_t *gpio);
void GPIO_Tgl(GPIO_t *gpio);
bool GPIO_In(GPIO_t *gpio);
void GPIO_Init(GPIO_t *gpio);

#endif