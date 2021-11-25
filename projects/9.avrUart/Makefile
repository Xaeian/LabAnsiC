MAIN_DIR = ./
MAIN_APP = main

CC = avr-gcc
OBJCOPY = avr-objcopy.exe
AVRDUDE := avrdude
CFLAGS = -g -Os -o
LFLAGS = -Os -mmcu=atmega328p -o
HFLAGS = -j .text -j .data -O ihex
DUDEFLAGS = -c usbasp -p m328p -U flash:w:$(MAIN_DIR)$(MAIN_APP).hex:i

SRC = $(MAIN_APP).c
SRC += lib/gpio.c
SRC +=

INCLUDE = -I.
INCLUDE +=

Burn : Build
	$(AVRDUDE) $(DUDEFLAGS)

Build : $(MAIN_APP).elf
	$(OBJCOPY) $(HFLAGS) $< $(MAIN_APP).hex
	
$(MAIN_APP).elf: $(MAIN_APP).o
	$(CC) $(SRC) $(INCLUDE) $(LFLAGS) $@
	
$(MAIN_APP).o:$(SRC)
	$(CC) $^ $(INCLUDE) $(CFLAGS) $@