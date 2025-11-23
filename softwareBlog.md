# Automatic Window Fan Hardware Details

## Hardware Background

See the [Hardware Details](/hardwareBlog.md) for a more in depth explanation. However in summary, we're running a arduino nano clone, and we have 3 I2C peripherals (two temperature sensors and one display), two PWM outputs (PWM Fan control and a mini servo), and one button type input (rotary encoder).

## Phase 1: Toolchain setup, and simple blinking LED.

The goal of this phase is to set up the toolchain to write code to the microcontroller, and demonstrate this with a simple blinking LED script.

I started by installing PlatformIO in vscode as my IDE and toolchain of choice, I then started a new project and used the built in arduino drivers to make a quick blinking LED script to make sure the toolchain is working.

## Phase 2: Driver Implementation

The goal of this phase is to develop drivers for all the peripherals, as well as other hardware specific functions like timers, and a serial connection to the host for debugging.

## Phase 3: Application Implementation

The goal of this phase is to implement the application logic using these drivers.