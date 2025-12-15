#pragma once


/**
 * Starts the system timer
 */
void time_init();


/**
 * Returns count of milliseconds since timer start
 */
uint32_t millis();


/**
 * Starts and monitors timer and toggles built in led once per second
 * @warning This function does not return, ment for debug use only
 */
void time_validate();