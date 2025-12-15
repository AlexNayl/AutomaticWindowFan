#include<avr/io.h>
#include"UART.h"
#include<util/delay.h>
#include"UART/printf.h"
/**
 * Sets up microcontroller for UART
*/
void UART_init () {
	unsigned int ubrr = 103; // Set baud rate to 9600
	UBRR0L = (unsigned char)ubrr;
	UBRR0H = (unsigned char)(ubrr>>8);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); // Enable transmitter and receiver
	//Leaving frame format as default, 8N1
}

/**
 * Transmits a single character.
 */
inline void UART_putc(unsigned char c){
	// wait for transmit buffer to be empty
    while(!(UCSR0A & (1 << UDRE0)));

    // load data into transmit register
    UDR0 = c;
}

/**
 * Transmits a string.
 * @param s Null terminated c-string
 */
void UART_puts(char* s){
	while (*s > 0){
		//while were not at a null character
		// wait for transmit buffer to be empty
    	while(!(UCSR0A & (1 << UDRE0)));
		//put the character and advance the pointer
		UDR0 = *s++;
	}
}

/**
 * Transmits a test message to validate driver works.
 * @warning This function does not return! Ment for debugging use only.
 */
void UART_validate(){
	UART_init();
	DDRB = DDRB | (1 << DDB5);
	unsigned int counter = 0;

	while(1){
		UART_printf("this is a test: %i\n", counter++);
		_delay_ms(1000);
	}
}

/**
 * implementation needed to use the tiny printf library
 */
void _putchar(char character){
	UART_putc(character);
}



