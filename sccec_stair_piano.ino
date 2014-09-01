/*
 * speaker_pcm
 *
 * Plays 8-bit PCM audio on pin 11 using pulse-width modulation (PWM).
 * For Arduino with Atmega168 at 16 MHz.
 *
 * Uses two timers. The first changes the sample value 8000 times a second.
 * The second holds pin 11 high for 0-255 ticks out of a 256-tick cycle,
 * depending on sample value. The second timer repeats 62500 times per second
 * (16000000 / 256), much faster than the playback rate (8000 Hz), so
 * it almost sounds halfway decent, just really quiet on a PC speaker.
 *
 * Takes over Timer 1 (16-bit) for the 8000 Hz timer. This breaks PWM
 * (analogWrite()) for Arduino pins 9 and 10. Takes Timer 2 (8-bit)
 * for the pulse width modulation, breaking PWM for pins 11 & 3.
 *
 * References:
 *     http://www.uchobby.com/index.php/2007/11/11/arduino-sound-part-1/
 *     http://www.atmel.com/dyn/resources/prod_documents/doc2542.pdf
 *     http://www.evilmadscientist.com/article.php/avrdac
 *     http://gonium.net/md/2006/12/27/i-will-think-before-i-code/
 *     http://fly.cc.fer.hr/GDM/articles/sndmus/speaker2.html
 *     http://www.gamedev.net/reference/articles/article442.asp
 *
 * Michael Smith <michael@hurts.ca>
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
