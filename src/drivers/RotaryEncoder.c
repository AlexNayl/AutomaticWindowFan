#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "RotaryEncoder.h"
#include "SystemTime.h"

const uint32_t DEBOUNCE_TIME = 5; //ms

enum PinState {
    Low,
    RisingDebounce,     //maybe rising, but not yet confirmed via debounce delay
    //Rising,             //confirmed rising, not yet handled UNUSED
    High,
    FallingDebounce,    //maybe falling, but not yet confirmed via debounce delay
    Falling             //confirmed falling, not yet handled
};

struct Pin{
    enum PinState state;
    uint32_t lastChangeTime;
    const uint8_t pinMask;
    const volatile uint8_t *pinReference;
};

// Note, init function assumes using port C, change that if changing port
volatile struct Pin buttonPin = {
    .state = High,
    .lastChangeTime = 0,
    .pinMask = 0b00001000,
    .pinReference = &PINC
};

volatile struct Pin rotaryPin = {
    .state = High,
    .lastChangeTime = 0,
    .pinMask = 0b00000100,
    .pinReference = &PINC
};

volatile struct Pin directionPin = {
    .state = High,
    .lastChangeTime = 0,
    .pinMask = 0b00000010,
    .pinReference = &PINC
};

/**
 * checks hardware pin states
 */
void resolvePins(){
    //examine my debouncing spaghetti code and despair
    volatile struct Pin* PIN_LIST[] = {&buttonPin,&rotaryPin,&directionPin};
    const uint8_t N = 3;

    //for each pin
    for( uint8_t i = 0; i < N; i++){
        volatile struct Pin* current_pin = PIN_LIST[i];

        if ((*(current_pin->pinReference) & current_pin->pinMask) > 0){
            //hardware pin high
            if(current_pin->state == Low){
                current_pin->lastChangeTime = millis() + DEBOUNCE_TIME;
                current_pin->state = RisingDebounce;
            }else if (current_pin->state == RisingDebounce && current_pin->lastChangeTime < millis()){
                current_pin->state = High;
                //we dont have any rising events, so skip it and just go to high
            }else if (current_pin->state == FallingDebounce && current_pin->lastChangeTime < millis()){
                //debounce failed, reset to high
                current_pin->state = High;
            }
        }else{
            //hardware pin low
            if(current_pin->state == High){
                current_pin->lastChangeTime = millis() + DEBOUNCE_TIME;
                current_pin->state = FallingDebounce;
            }else if (current_pin->state == FallingDebounce && current_pin->lastChangeTime < millis()){
                current_pin->state = Falling;
                //this state will be checked during polling and will trigger an event
            }
            else if (current_pin->state == RisingDebounce && current_pin->lastChangeTime < millis()){
                current_pin->state = Low;
                //debounce failed, reset to low
            }
        }
    }
};

/**
 * Interrupt handler for port C io.
 */
ISR(PCINT1_vect){
   resolvePins();
}

/**
 * Initializes pins and interrupts for the rotary encoder.
 */
void rotary_init(){
    //setup pins
    DDRC &= ~(buttonPin.pinMask | rotaryPin.pinMask | directionPin.pinMask); //set pins to input by forcing their bits to 0 (technically done by default, but best to set state in code)
    PORTC |= (buttonPin.pinMask | rotaryPin.pinMask | directionPin.pinMask); //set pins to high while in input mode to enable pull up resisters

    //setup interrupts
    cli();
    PCICR |= 0b00000010;    //enable port C interrupts
    PCMSK1 |= (buttonPin.pinMask | rotaryPin.pinMask | directionPin.pinMask);   //enable interrupts for pins
    sei();
}

/**
 * Checks if encoder was changed
 */
void rotary_poll(){
    resolvePins();

    if(buttonPin.state == Falling){
        //button pin event
    }
}

/**
 * Alternative poll that just outputs to UART if it detects a change.
 */
void rotary_debug_poll(){
    resolvePins();

    if(buttonPin.state == Falling){
        //button pin event
        UART_puts("Falling\n");
        buttonPin.state = Low;
    }
    
}

/**
 * Monitors rotary encoder and prints to UART when changed.
 * @warning This function does not return! Ment for debugging use only.
 */
void rotary_validate(){
    time_init();
    rotary_init();
    UART_init();
    while(1){
        rotary_debug_poll();
    }
}