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
![Breadboard](/Resources/Breadboard.jpg "Completed Breadboard Phase")
The goal of this phase is to provide a platform for software development testing while also making sure that all the components work together before they're soldered together.

I started by identifying which pin types I'll need to control all my selected peripherals, the screen and temperature controller are simple as they're just I2C, connecting to pins A4 and A5. The rotary encoder needs 3 digital pins, for the 2 direction pins and the button, I used A1/A2/A3 for convenience, but I can change that in the soldered version. Next the servo and fan need PWM from the arduino for control, I did a little research into how the ATmega328P does PWM output, and I selected D9 and D3 since they're on separate timers, so they should be easier to configure. Finally, the fan RPM sensor can connect to any digital input, I have it in D10 for convenience.

Next, planning power delivery, the plan is to take 5 volt USB power off the arduino in the final product, so I wired that into the outside rail. From this the servo, temperature sensors, and screen are power directly, and the boost converter for the fan is also powered. To be able to get full power out of the fan a boost converter is needed to get 12 volts. Lastly, the rotary encoder needed 2 ground reference wires also coming from the power rails.

I'm noticing a significant voltage drop in the power rail when I have everything plugged in and the fan running. It seems to be 3.8 volts to 4 volts depending on what source I plug it into. I added a second set of power wires (not pictured) to reduce resistance due to poor contact, it seemed to help a little. Hopefully this wont cause problems with the peripherals while I'm writing the code. And hopefully the issue reduces when I solder the final version together.

## Permanent Protoboard Phase
The goal of this phase is to create the final protoboard based main board for installation into the 3d printed device. This will be done after the peripheral drivers are written and tested using the breadboard to make sure everything can work together.

## Final Installation
The goal of this phase is to draft, model, and print the device structure, and assemble for testing and deployment.