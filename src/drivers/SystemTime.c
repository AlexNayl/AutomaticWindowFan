#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include "SystemTime.h"
/**
 * count of time in miliseconds (overflows in approx 50 days)
 */
volatile uint32_t tick = 0;

/**
 * timeout to trigger system restart before timer overflow
 */
const TIMEOUT_LIMIT = UINT32_MAX - 10000;   //ten seconds before overflow

void time_init(){
    /**
     * URL: https://dbuezas.github.io/arduino-web-timers/#mcu=ATMEGA328P&timer=0&topValue=0xFF&clockPrescalerOrSource=1024&FCPU_UI=16Mhz&InterruptOnTimerOverflow=on&CompareOutputModeA=disconnect
     * Mode     : Normal
     * Period   : 1.024 ms
     * Frequency: 976.5625 Hz
     * Outputs  : none
     */
    cli();
    TCCR0B = 
        1 << CS01 |
        1 << CS00;
    TIMSK0 = 
        1 << TOIE0;

    sei();
}


ISR(TIMER0_OVF_vect) {
    /* on overflow */
    tick++;
    if(tick >= TIMEOUT_LIMIT){
        //on timeout, reset by forcing the watch dog timer
        wdt_enable(WDTO_15MS);
    }
}

uint32_t millis(){
    uint32_t out;
    cli();
    out = tick;
    sei();
    return out;
}

void time_validate(){
    time_init();
    DDRB |= (1 << PB5); // Set PB5 (Arduino pin 13) as output
    uint32_t last_flash = 0;

    while (1){
        if (last_flash + 1000 < millis()){
            //toggle pin B5
            PORTB ^= (1 << PB5);
            last_flash = millis();
        }
        
    }
}