#define __AVR_ATmega328P__
#define F_CPU 16000000

#include <avr/io.h>
#include "gpio.h"

void GPIO_Set(GPIO_t *gpio)
{
  if(gpio->invert) GPIO_PORT(gpio->_gpio) &= ~(1 << gpio->_pin);
  else GPIO_PORT(gpio->_gpio) |= 1 << gpio->_pin;
  gpio->set = true;
}

void GPIO_Rst(GPIO_t *gpio)
{
  if(gpio->invert) GPIO_PORT(gpio->_gpio) |= 1 << gpio->_pin;
  else GPIO_PORT(gpio->_gpio) &= ~(1 << gpio->_pin);
  gpio->set = false;
}

void GPIO_Tgl(GPIO_t *gpio)
{
  GPIO_PORT(gpio->_gpio) ^= 1 << gpio->_pin;
}

bool GPIO_In(GPIO_t *gpio)
{
  uint8_t in = GPIO_PIN(gpio->_gpio);
  if(gpio->invert) in = ~in;
  return in & (1 << gpio->_pin);
}

void GPIO_Init(GPIO_t *gpio)
{
  if(gpio->pin < 8)  {
    gpio->_gpio = GPIOD;
    gpio->_pin = gpio->pin;
  }
  else if(gpio->pin < 14) {
    gpio->_gpio = GPIOB;
    gpio->_pin = (gpio->pin) - 8;
  }
  else if(gpio->pin < 20) {
    gpio->_gpio = GPIOC;
    gpio->_pin = (gpio->pin) - 14;
  }
  else return;
  
  if(gpio->mode == GPIO_MODE_Output) {
    GPIO_DDR(gpio->_gpio) |= 1 << gpio->_pin;
    if(gpio->set) GPIO_Set(gpio);
    else GPIO_Rst(gpio);
  }
  else {
    GPIO_DDR(gpio->_gpio) &= ~(1 << gpio->_pin);
    if(gpio->pullup) GPIO_PORT(gpio->_gpio) |= 1 << gpio->_pin;
    else GPIO_PORT(gpio->_gpio) &= ~(1 << gpio->_pin);
  }
}