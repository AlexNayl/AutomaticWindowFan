#pragma once

#include<util/twi.h>
//Two wire interface, aka I2C

/**
 * Called at system startup to prepare the TWI circuits for use
 */
void TWI_init();

/**
 * Sends start condition
 */
void TWI_start();

/**
 * Sends stop condition
 */
void TWI_stop();

/**
 * Sends one byte of data
 */
void TWI_write(uint8_t data);

/**
 * reads one byte and sends an acknowledgment signal (tells sender to continue transmiting)
 */
uint8_t TWI_readACK();

/**
 * reads one byte and does not send an acknowledgment signal (tells sender to stop transmiting)
 */
uint8_t TWI_readNACK();