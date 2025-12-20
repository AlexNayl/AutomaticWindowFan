#include <avr/io.h>
#include <avr/wdt.h>
#include "drivers/UART.h"
#include "drivers/RotaryEncoder.h"
#include "drivers/SystemTime.h"

int main(void){
	//init
	wdt_disable();


	//run
	time_validate();
}