# Automatic Window Fan Hardware Details

As a software developer I'm keeping the hardware intentionally simple, using pre made modules talking together with I2C. However this project still demonstrates my knowledge as to how electronics work and are structured.

## Hardware Selection
| Device                    | Source                             | Description / Usage	|
|----------|-------------|--------------|
| Arduino Nano Clone        | Spare in my electronics supplies.  | Primary micro controller, I had it spare and it has enough IO for what I need.	|
| 120mm 4Pin Computer Fan   | [Amazon](www.amazon.ca/dp/B0BNHTPQR9)	| Primary air mover, 4pin allows me to control it precisely via PWM from the micro controller for soft startup and shutdown.	|
| I2C Based Temperature Sensors	| [Amazon](www.amazon.ca/dp/B088D32F4P)	| Two needed to monitor inside and outside temperatures, humidity is a nice bonus.	|
| I2C Based Display Module	| [Amazon](www.amazon.ca/dp/B0C7L289Y2)	| Needed to show user the current temperature and the set temperature, OLED selected for visibility in low light conditions while not contributing excessive light bleed into the room, critical for bedrooms.	|
| DC to DC Boost Converter	| [Amazon](www.amazon.ca/dp/B07DK82HS8)	| Needed to supply the 12 volts to power the fan from the 5 volt USB supply. |
| Basic 360 Degree Rotary Encoder 	| Spare in my electronics supplies.	| Primary user interaction mechanism. |
| Micro Servo	| Spare in my electronics supplies. | Used to open and close the damper to prevent drafts when fan is not running. |

## Breadboard Phase
The goal of this phase is to provide a platform for software development testing while also making sure that all the components work together before they're soldered together.

## Permanent Protoboard Phase
The goal of this phase is to create the final protoboard based main board for installation into the 3d printed device. This will be done after the peripheral drivers are written and tested using the breadboard to make sure everything can work together.

## Final Installation
The goal of this phase is to draft, model, and print the device structure, and assemble for testing and deployment.