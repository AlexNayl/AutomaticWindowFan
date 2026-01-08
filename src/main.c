#include <avr/io.h>
#include <avr/wdt.h>
#include "drivers/UART.h"
#include "drivers/RotaryEncoder.h"
#include "drivers/SystemTime.h"

int main(void){
	//init
	//disable watchdog timer to prevent reset loop, this time is used in some cases as a software reset trigger
	wdt_disable();
	wdt_reset();


	//run
	rotary_validate();
}