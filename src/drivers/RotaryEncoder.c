#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "RotaryEncoder.h"

// Note, init function assumes using port C, change that if changing prot
const uint8_t BUTTON_PIN = 0b00001000;
const uint8_t ROTARY_PIN = 0b00000100;
const uint8_t DIR_PIN = 0b00000010;

/**
 * Set during interrupt to indicate encoder was turned, and how many steps in which direction was it turned since last poll.
 */
volatile int8_t detectedRotation = 0;

/**
 * Set during interrupt to indicate button was pressed since last poll.
 */
volatile uint8_t detectedButtonPress = 0;

/**
 * Debug use
 */

volatile uint8_t interruptFired = 0;


/**
 * Interrupt handler for port C io.
 */
ISR(PCINT1_vect){
    if ((PINC & BUTTON_PIN) == 0){
        detectedButtonPress++;
    }

    if ((PINC & ROTARY_PIN) == 0){
        if ((PINC & DIR_PIN) == 0){
            detectedRotation++;
        }else{
            detectedRotation--;
        }
    }
    
}

/**
 * Initializes pins and interrupts for the rotary encoder.
 */
void rotary_init(){
    //setup pins
    DDRC &= ~(BUTTON_PIN | ROTARY_PIN | DIR_PIN); //set pins to input by forcing their bits to 0 (technically done by default, but best to set state in code)
    PORTC |= (BUTTON_PIN | ROTARY_PIN | DIR_PIN); //set pins to high while in input mode to enable pull up resisters

    //setup interrupts
    cli();
    PCICR |= 0b00000010;    //enable port C interrupts
    PCMSK1 |= (BUTTON_PIN | ROTARY_PIN);   //enable interrupts for pins C2 and C3 (rotation and press), (PCINT10,11)
    sei();
}

/**
 * Checks if encoder was changed, call relevant code if so, and reset encoder for next use.
 */
void rotary_poll(){
    if(detectedRotation != 0){
        //was turned
        detectedRotation = 0;
        //TODO handle
    }

    if(detectedButtonPress != 0){
        // was pressed
        detectedButtonPress = 0;
        //TODO handle
    }
}

/**
 * Alternative poll that just outputs to UART if it detects a change.
 */
void rotary_debug_poll(){
    if(detectedRotation != 0){
        //was turned
        UART_printf("%i\n", detectedRotation);

        detectedRotation = 0;

    }

    if(detectedButtonPress != 0){
        // was pressed
        detectedButtonPress = 0;
        UART_puts("0\n");
    }
}

/**
 * Monitors rotary encoder and prints to UART when changed.
 * @warning This function does not return! Ment for debugging use only.
 */
void rotary_validate(){
    rotary_init();
    UART_init();
    while(1){
        rotary_debug_poll();
    }
}