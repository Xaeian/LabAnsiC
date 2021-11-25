#define __AVR_ATmega328P__
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"

GPIO_t led = { .pin = 3, .mode = GPIO_MODE_Output, .invert = true };
GPIO_t sw = { .pin = 12, .mode = GPIO_MODE_Input, .pullup = true, .invert = true };

// Wygoda użycia
// Skalowalność
// Separacja modułów
// Hardeer <--> Aplikacja - oddzielnie
// Testy jednostkow modułów
// +/- częściowa wielplatformowość

int main2(void)
{
  GPIO_Init(&led);
  GPIO_Init(&sw);

  while (1)
  {
    if(GPIO_In(&sw))
    {
      GPIO_Set(&led);
    }
    else
    {
      GPIO_Rst(&led);
    }
  }
}

// Mniejszy narzut pamięci
// Szybciej wykonujący się kod

int main(void)
{
  DDRD |= (1 << 3);  // *****1***
  DDRB &= ~(1 << 4); // ****0****
  PORTB |= (1 << 4); // ****1****

  while (1)
  {
    if(~PINB & (1 << 4))
    {
      PORTD &= ~(1 << 3);
    }
    else
    {
      PORTD |= (1 << 3);
    }
  }
}