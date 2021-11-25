#define __AVR_ATmega328P__
#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>

#include "portx.h"
volatile uint8_t PORTX, PINX, PORTY[4];

//-------------------------------------------------------------------------------------------------

void PORT_Init()
{
	PORTX = 0; PORTY[0] = 0; PORTY[1] = 0; PORTY[2] = 0; PORTY[3] = 0;
	
	PORTB |= (1 << SPI_CS);
	DDRB |= (1 << SPI_SCK) | (1 << SPI_MOSI) | (1 << SPI_CS);
	DDRB &= ~(1 << SPI_MISO);
	SPCR = (1 << SPIE) | (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0); // Prescaler: 128
	
	PORTB &= ~(1 << SPI_CS);
	SPDR = PORTX;
  sei();
}

__inline void PORT_Stop() { SPCR &= ~(1<<SPIE); }
__inline void PORT_Start() { SPCR |= (1<<SPIE); }
  
void PORTY_Sign(uint8_t position, uint8_t sign, bool dot)
{
	switch(sign) {
    case 0: case '0': PORTY[position] = 0x3F; break;
    case 1: case '1': PORTY[position] = 0x06; break;
		// 2-9 a-f A b c d E F
	}

	if(dot) PORTY[position] |= (1<< 7);
}

void PORTY_Int(int16_t value)
{
	// TODO
}

//-------------------------------------------------------------------------------------------------

uint8_t portx_state;

ISR(SPI_STC_vect)
{
	switch(portx_state)
	{
		case 0: PINX = SPDR;
		case 1: case 2: case 3: SPDR = PORTY[portx_state]; break;
		case 4: PORTB |= (1 << SPI_CS); _delay_us(1); PORTB &= ~(1 << SPI_CS); SPDR = PORTX;
	}
	
	portx_state++;
	if(portx_state > 4) { portx_state = 0; }
}

//-------------------------------------------------------------------------------------------------