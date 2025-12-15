# Automatic Window Fan Hardware Details

## Hardware Background

See the [Hardware Details](/hardwareBlog.md) for a more in depth explanation. However in summary, we're running a arduino nano clone, and we have 3 I2C peripherals (two temperature sensors and one display), two PWM outputs (PWM Fan control and a mini servo), and one button type input (rotary encoder).

## Phase 1: Toolchain setup, and simple blinking LED.

The goal of this phase is to set up the toolchain to write code to the microcontroller, and demonstrate this with a simple blinking LED script.

I started by installing PlatformIO in vscode as my IDE and toolchain of choice, I then started a new project and used the built in arduino drivers to make a quick blinking LED script to make sure the toolchain is working. I then followed a quick tutorial to rewrite out the arduino drivers, instead using the definitions in avr/io.h.

## Phase 2: Driver Implementation

The goal of this phase is to develop drivers for all the peripherals, as well as other hardware specific functions like timers, and a serial connection to the host for debugging.

### UART / Serial output

This critical function is necessary to implement first because it allows me to print debug statements to a serial console so that I can debug and test the other drivers while I'm writing them. I started by reading the UART section of the ATmega328p data sheet, knowing that the Arduino Nano has a dedicated chip to convert UART to USB serial, I just need to figure out UART to be able to accomplish what I want. I implemented a startup and write function as recommended by the data sheet, and I was quickly writing basic strings to a serial console viewable on my computer.

But for debugging, I need to be able so see numbers of various kinds. To accomplish this I went online searching for a embedded version of the printf library, and I found [this library](https://github.com/mpaland/printf). I copied the files into a UART subfolder and followed the readme guide disabling unnecessary features like float, exponential, and long long support. I then implemented _putchar() as required, which allowed the platform independent library to communicate with my hardware. Finally, I made a define wrapper for printf() so it looks like UART_printf() similar and in the same location as my other functions.

This external library did add a few kilobytes to my flash usage, but I still have a lot left over so I don't think this will come back to haunt me.

### Rotary Encoder

I decided to implement this next as I thought this would be the simplest, since this encoder is basically wired like 3 buttons inputs. One of the inputs is for the press button, and the other two can be simplified to triggering when the encoder rotates, and which direction it rotates. I started by researching the microcontroller's interrupts, and I implemented a io interrupt handler for the relevant pins, planning on having them set flags and then dealing with it in a polling function of the main loop.

I then got a crash course in debouncing, throwing that plan out the window.

In order to implement software debouncing (without just stalling the whole program while we wait for the input to settle), I had to figure out timers. And in the spirit of learning more about real world embedded development, I decided to implement a global timer that I can read seconds and milliseconds from at any time. This is a bit more complex then just dedicating a timer to debouncing, but being able to read a global time will almost certainly be useful as development continues.

## Phase 3: Application Implementation

The goal of this phase is to implement the application logic using these drivers.