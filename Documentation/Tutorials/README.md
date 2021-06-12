# Getting Started

Shortcuts for those who don't want to read:
- [Hardware Setup](#choose-your-hardware)
- [Software Tutorials](#tutorials)
- [Serial Connection for Windows](Tutorial-Windows-Serial.md)

**New to Pokémon automation? This is what this guide is for!**

This guide will walk you through the entire process of automating your game.
This includes everything from what hardware to purchase, to setting it all up, to running them on your Switch.

But before we begin, we must first introduce some background and terminology.

This project automates Pokémon Sword/Shield (and Nintendo Switch in general) using a microcontroller that fakes as a wired game controller.
But instead of a human pressing buttons, it is the microcontroller that is doing it - albeit electronically without moving parts.
From here on down, we will call this microcontroller the "device".

There are many different devices that can be used for this purpose.
The most common is the [Arduino](https://store.arduino.cc/usa/arduino-uno-rev3) (the namesake of this project). Others that we support include the [Teensy](https://www.pjrc.com/teensy/) and the [Pro Micro](https://deskthority.net/wiki/Arduino_Pro_Micro).
(Though we no longer recommend the Arduino.)

The device by itself is sufficient for simple programs. More advanced programs will require communication with a computer.
This is done using a [serial connection](https://en.wikipedia.org/wiki/Serial_port).

The device with a serial connection to a computer will allow a computer to control your Switch.
But any programs running with this setup are still "blind" in that they cannot see the Switch screen or hear any sounds.
Thus this leads to the final component, "feedback". Feedback is where the program can utilize video and/or sound information from the Switch.
This is done using a capture device such as a capture card that is used by streamers.

<img src="images/basic-setup.jpg" height="600">


# Choose your Automation Level

As hinted in the previous section, there are multiple levels of automation. If you are getting into automation, you will need to choose which level you wish to pursue.

1. **Basic Programs** - No computer control. No feedback. Device runs completely autonomously.
2. **Serial Programs** - Computer control. No feedback.
3. **Full Feedback** - Computer control with video feedback.

The first level is the simplest and is where everybody should start. But it is also the most limited in the programs that can run.
Each successive level is more complicated to setup and requires additional hardware. But it expands the pool of programs that can be run.

Only the highest level (full feedback) is it possible to run advanced programs like automatic Dynamax Adventures.

## Basic Programs

Basic programs have no computer control and no feedback. These programs are completely blind and cannot see the video or hear any sounds.

The hardware required for basic programs is the simplest. All you need is the device and an adapter/cable to connect it to the Switch.

The list of programs that can be run with the basic setup [is here](../ProgramList.md#native-programs).

<img src="../NativePrograms/images/DateSpam-LotoFarmer.png" width="800">

## Serial Programs

The next step up is to add serial connectivity between the device and a computer. This allows your computer to control your device and therefore your Switch.
Serial programs run on the computer with the device acting as a proxy.

Since serial programs reside on the computer, they are less limited* by the memory limitations of the device. This allows serial programs to be much more sophisticated. Furthermore, a computer can control multiple devices (and therefore Switches) simultaneously. Thus you can have multi-Switch programs.

Serial connectivity will allow you to run the SerialPrograms package which has most of the basic programs as well as the [serial programs](../ProgramList.md#serial-programs).

When combined with video capture, you can play your Switch on your computer and easily fire off programs with just a few clicks.

Thus you now have tool-assisted gameplay. This can be useful for many things - such as getting into a crowded Max Raid that has a complicated raid code.

<img src="images/serial-setup.jpg" height="330"> <img src="images/serial-programs-0.png" height="330">

***Important:** You will need a fairly powerful computer to handle serial programs with video feedback. For a single Switch with video feedback, we recommend a quad core computer no older than 2015. If you want to run 4 Switches all with feedback, we recommend a modern 8-core computer. The computer must also be running 64-bit Windows, though plan to extend support to other operating systems in the future.*

**For reasons involving latency, many of the "fast" programs cannot run reliably over a serial connection. These programs partially remain on the device. For this reason, PABotBase has a library of subroutines that handle these timing-sensitive operations. Unfortunately, this library is too large to fit onto the Arduino Uno R3. Therefore, the Arduino Uno R3 cannot run all the programs in our serial programs package even though the device is supposed to be just a proxy.*

## Full Feedback

Full feedback extends serial connectivity with video recogition to produce programs that respond to and adapt to game events. At this point, the program is imitating a human player who can see the screen and hear sounds.

Full feedback enables the most powerful programs that are available. For example:
- [Automatic purple beam finding.](../SerialPrograms/PurpleBeamFinder.md)
- Autonomous shiny hunting with automatic shiny detection. (example: [Regigigas](../SerialPrograms/ShinyHuntAutonomous-Regigigas2.md))
- The [AutoMaxLair prototype](https://github.com/PokemonAutomation/AutoMaxLair).

<img src="../SerialPrograms/images/ShinyHuntAutonomous-Regigigas2.jpg" width="800">
<img src="images/automaxlair-prototype.jpg" height="400">

# Choose your Hardware

In addition to choosing what level of automation you wish to achieve, you must also choose the device that you will use to control your Switch.

These are the list of the devices that we support. Click on the links for the setup guide for the device.

- [Hardware Setup: Teensy 2.0 and Teensy++ 2.0](Hardware-Teensy2.md)
- [Hardware Setup: Pro Micro](Hardware-ProMicro.md)
- [Hardware Setup: Arduino Uno R3](Hardware-ArduinoUnoR3.md) (not recommended)

For first time users, we recommend the Teensy 2.0. It is somewhat expensive, but is by far the most user-friendly. You get what you pay for.

For experienced users looking to automate multiple Switches for serial programs and want to reduce the cost, we recommend the Pro Micro.
The Pro Micro board is very cheap when purchased in quantity. But it is difficult and annoying to flash. Thus we recommend it only for PABotBase which you flash just once to use all the serial programs.

***We DO NOT recommend the Arduino Uno R3 under any circumstance. (Details are in the link for Arduino above.)
This option is only here for legacy purposes and for those who already have the hardware.***


# Tutorials

Which tutorial you use will depend on what operating system you are using and what board/device you have chosen.

 | Device | Windows | Mac
 | --- | --- | ---
 | [Teensy 2.0 and Teensy++ 2.0](Hardware-Teensy2.md)           | [Native Programs](Tutorial-Windows-Teensy2.md)<br>[Serial Programs](Tutorial-Windows-Serial.md)      | [Native Programs](Tutorial-Mac-Teensy2.md)
 | [Pro Micro](Hardware-ProMicro.md)                            | [Native Programs](Tutorial-Windows-ProMicro.md)<br>[Serial Programs](Tutorial-Windows-Serial.md)       | [Native Programs](Tutorial-Mac-ArduinoProMicro.md)
 | [Arduino Uno R3](Hardware-ArduinoUnoR3.md) (not recommended) | [Native Programs](Tutorial-Windows-ArduinoUnoR3.md)<br>[Serial Programs](Tutorial-Windows-Serial.md)   | [Native Programs](Tutorial-Mac-ArduinoProMicro.md)



<hr>

**Back to:**
- [Project Home](/README.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
