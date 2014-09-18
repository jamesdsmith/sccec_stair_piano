/*
 * Sierra College Computer Engineering Club
 * Staircase Piano Project
 * author: James Smith
 */

#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

const int buttonPin1 = 4;
const int buttonPin2 = 9;

const int analogPin1 = 2;
const int IRpin = 6;

#include "buttonStates.h"
struct buttonState button1;
struct buttonState button2;
struct buttonState analog1;
struct buttonState IRbutton;

#include "playFunctions.h"
#include "c_tone.h"
#include "d_tone.h"
//#include "tone2.h"

void setup()
{
  pinMode( speakerPin, OUTPUT );
  pinMode( buttonPin1, INPUT );
  pinMode( buttonPin2, INPUT );
  pinMode( analogPin1, INPUT );
  pinMode( IRpin, INPUT );
  Serial.begin(9600);
}

void loop()
{
  updateDigitalButton( &button1, buttonPin1 );
  updateDigitalButton( &button2, buttonPin2 );
  updateInvAnalogButton( &analog1, analogPin1, 100 );
  updateDigitalButton( &IRbutton, IRpin );
  
  Serial.println( analogRead( analogPin1 ) );
  
  if( analog1.Pressed )
  //if( analog1.Pressed && !bPlaying )
  {
    startPlayback( c_data, c_length, 0 );
  }
  if( button2.Pressed )
  {
    startPlayback( d_data, d_length, 1 );
    Serial.println("Pressed 2");
  }
}
