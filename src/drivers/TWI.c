#include "TWI.h"



// expanded off code from https://github.com/abmj01/ATmega328p_I2C

//#define F_CPU 16000000UL  // assuming using 16MHz internal oscillator
#define TWI_BIT_RATE_REG_SETTING ((F_CPU / 100000UL) / 2) - 8 // For 100kHz SCL

void TWI_init() {
	TWSR = 0x00;  // set prescaler to 1
	TWBR = TWI_BIT_RATE_REG_SETTING;  // SCL frequency is 100 kHz @ 16 MHz F_CPU
}

void TWI_start() {
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); //Send START condition
	while (!(TWCR & (1 << TWINT))); // Wait for TWINT FLag set. This indicates that the START condition has been transmitted
}

void TWI_stop() {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

void TWI_write(uint8_t data) {
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
}

uint8_t TWI_readACK() {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

uint8_t TWI_readNACK() {
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}