#ifndef UART_DRIVER
#define UART_DRIVER

#include "UART/printf.h"
//wrapper for tiny printf library
#define UART_printf printf_

/**
 * Sets up microcontroller for UART
*/
void UART_init ();

/**
 * Transmits a single character.
 */
void UART_putc(unsigned char c);

/**
 * Transmits a string.
 * @param s Null terminated c-string
 */
void UART_puts(char* s);

/**
 * Transmits a test message to validate driver works.
 * @warning This function does not return! Ment for debugging use only.
 */
void UART_validate();



#endif // UART_DRIVER