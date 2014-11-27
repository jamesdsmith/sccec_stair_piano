/*
 * Sierra College Computer Engineering Club
 * Staircase Piano Project
 * author: James Smith
 * 
 * This is the Arduino side of the stair project. The Arduino will use the buttonStates
 * library on 8 analog inputs to detect analog button presses (coming from laser pointers
 * pointed at photoresistors) and will keep track of which buttons have been pressed
 * by each setting a bit in a byte. The RPi will request this byte at a specific interval
 * over the I2C connection, and then the Arduino will reset the state and start tracking
 * more button presses.
 *
 * Requires an Arduino Mega, or any Arduino that has at least 10 analog inputs (8 for
 * button presses, 2 for I2C). This project could also be run on an Uno using digital
 * button presses.
 * 
 * TODO: Need to setup button code for all of the analog buttons, just using digital
 * buttons for now as placeholders
 */

#include <Wire.h>

// sets our address for the I2C connection
// The Arduino is setup to be a slave to the RPi
#define SLAVE_ADDRESS 0x04

const int analogPin1 = 0;
const int analogPin2 = 1;
const int analogPin3 = 2;
const int analogPin4 = 3;
const int analogPin5 = 4;
const int analogPin6 = 5;
const int analogPin7 = 6;
const int analogPin8 = 7;

#include "buttonStates.h"
struct buttonState analog1;
struct buttonState analog2;
struct buttonState analog3;
struct buttonState analog4;
struct buttonState analog5;
struct buttonState analog6;
struct buttonState analog7;
struct buttonState analog8;

// each bit in this byte will hold the key state for exactly one button, until that state data
// is transferred to the RPi over I2C
byte keyState = 0;

// analog trigger threshold. This is dependent on the ambient light
int threshold = 700;

#define NOTE_1 0x01
#define NOTE_2 0x02
#define NOTE_3 0x04
#define NOTE_4 0x08
#define NOTE_5 0x10
#define NOTE_6 0x20
#define NOTE_7 0x40
#define NOTE_8 0x80

void setup()
{
  Serial.begin(9600);
  pinMode( analogPin1, INPUT );
  pinMode( analogPin2, INPUT );
  pinMode( analogPin3, INPUT );
  pinMode( analogPin4, INPUT );
  pinMode( analogPin5, INPUT );
  pinMode( analogPin6, INPUT );
  pinMode( analogPin7, INPUT );
  pinMode( analogPin8, INPUT );

  // Setup I2C
  Wire.begin( SLAVE_ADDRESS );
  Wire.onRequest( sendData );
}
int lastState;
void loop()
{
  updateInvAnalogButton( &analog1, analogPin1, threshold );
  updateInvAnalogButton( &analog2, analogPin2, threshold );
  updateInvAnalogButton( &analog3, analogPin3, threshold );
  updateInvAnalogButton( &analog4, analogPin4, threshold );
  updateInvAnalogButton( &analog5, analogPin5, threshold );
  updateInvAnalogButton( &analog6, analogPin6, threshold );
  updateInvAnalogButton( &analog7, analogPin7, threshold );
  updateInvAnalogButton( &analog8, analogPin8, threshold );
  
  if( analog1.Pressed )
  {
    keyState |= NOTE_1;
  }
  if( analog2.Pressed )
  {
    keyState |= NOTE_2;
  }
  if( analog3.Pressed )
  {
    keyState |= NOTE_3;
  }
  if( analog4.Pressed )
  {
    keyState |= NOTE_4;
  }
  if( analog5.Pressed )
  {
    keyState |= NOTE_5;
  }
  if( analog6.Pressed )
  {
    keyState |= NOTE_6;
  }
  if( analog7.Pressed )
  {
    keyState |= NOTE_7;
  }
  if( analog8.Pressed )
  {
    keyState |= NOTE_8;
  }
}

// Send data to the RPi over the Wire protocol (I2C)
void sendData()
{
  Wire.write( keyState );
  keyState = 0;
}
