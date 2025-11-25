# AutomaticWindowFan
An embedded software and hardware project creating a temperature controlled window fan.

![Breadboard](/Resources/Breadboard.jpg "Completed Breadboard Phase")

## Background
I like to sleep in a cold room, but my family like to keep the house warm at night, as a result I often crack open the window to let some cold air in, but its very hard to regulate the room temperature this way. I started to think about using a computer fan and a thermostat to regulate the room temperature for me, and the more I thought about it, the more I realized that this project could be scaled up to demonstrate a lot of aspects of electronics design and embedded development.

## Requirements

- **Must be coded in embedded C, using industry style tool chain.** The main purpose of this project is to teach me how embedded software is developed in the real world, so arduino scripts aren't going to cut it here.

- **Must hold the room to within 1 degree celsius when conditions allow.** External air temperatures wont always allow for this.

- **Must not operate when outside air temperature works against target room temperature.** If its a hot summers night, bringing in outside air probably wont cool the room down. An outside air temperature monitor will be needed.

- **Target temperature must be user settable via interactive display.** We can also display other neat info like current inside and outside temperature and fan speed.

- **An automatic damper must be included to prevent drafts.** We'll attach a micro servo to a flap to do this.

# Project Plans/Blogs

These pages will be sparse at first, but I'll add to them as I complete milestones in this project.
[Software Details](/softwareBlog.md)
[Hardware Details](/hardwareBlog.md)