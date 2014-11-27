sccec_stair_piano
=================

Contains all the code and files necessary for the Sierra College Computer Engineering Club's staircase piano project

The project is intended to be installed on a staircase. Laser modules will shoot a laser across the surface of the stairs at a photoresistor, which is hooked into an analog pin on an Arduino. When the person's foot breaks the beam of the laser, the resistance of the photoresistor will decrease and the current to the pin will drop. This will be detected in code, and stored as a state variable on the Arduino.

A Raspberry Pi will communicate with the Arduino over I2C, and will periodically ask the Arduino for the state variable. Reading this state variable will allow the RPi to determine which lasers are blocked, and will play the appropriate sound.

#### Schematic
![Stair Piano Schematic](/docs/schematic_bb.png?raw=true "Stair Piano Schematic")

### Requirements:
* Arduino Mega 2560
  * Uno or smaller Arduino usable with 4 or less steps (2 analog pins needed for I2C)
* Raspberry Pi
  * Libraries: SDL, SDL_mixer, i2c-dev
* Components:
  * 8x Photoresistors
  * 8x 1kΩ Resistors
  * 8x 5mW Laser Modules
