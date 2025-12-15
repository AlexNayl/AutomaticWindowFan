#pragma once

/**
 * Initializes pins and interrupts for the rotary encoder.
 */
void rotary_init();

/**
 * Checks if encoder was changed, call relevant code if so, and reset encoder for next use.
 */
void rotary_poll();

/**
 * Monitors rotary encoder and prints to UART when changed.
 * @warning This function does not return! Ment for debugging use only.
 */
void rotary_validate();