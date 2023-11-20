#define __AVR_ATmega328P__
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"

/**
 * Zalety pracy bezpośrednio na rejestrach (+)
 * - Nie wymaga pisania biblioteki
 * - Mniejszy narzut pamięci FLASH i RAM
 * - Szybciej wykonujący się kod
 * - Szybsza realizacja projektu od zera
 * - Wymaga mniejszej wiedzy w zakresie znajomości języka 'c'
 */
int ConceptOnRegisters(void)
{
  DDRD |= (1 << 3);  // DDRD  = |?|?|?|?|1|?|?|?|
  DDRB &= ~(1 << 4); // DDRB  = |?|?|?|0|?|?|?|?|
  PORTB |= (1 << 4); // PORTB = |?|?|?|1|?|?|?|?|

  while (1)
  {
    if(~PINB & (1 << 4)) // if(press)
    {
      PORTD &= ~(1 << 3); // led-on
    }
    else
    {
      PORTD |= (1 << 3); // led-off
    }
  }
}

GPIO_t led = { .pin = 3, .mode = GPIO_MODE_Output, .invert = true };
GPIO_t sw = { .pin = 12, .mode = GPIO_MODE_Input, .pullup = true, .invert = true };

/**
 * Zalety podejścia strukturalnego (+)
 * - Wygoda użycia, czytelność (bardziej zrozumiały kod, podpowiedzi IDE, separacja 'modułów')
 * - Oddzielenie hardware'u od aplikacji
 *  - Możliwość niezależnego rozwoju funkcjonalności peryferiów i aplikacji
 *  - Znacznie łatwiejsze testy jednostkowe
 *  - Względna 'wieloplatformowość' aplikacji
 * - Lepsza skalowalność aplikacji (w przypadku wielokrotnego używania struktur)
 * - Szybsza realizacja kolejnych projektów
 */
int ConceptOnStructures(void)
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


int main(void)
{
  //Structures();
  //Register();
}