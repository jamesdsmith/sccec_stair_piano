#ifndef _BUTTONSTATES_H_
#define _BUTTONSTATES_H_

/*
 * ButtonState Library
 * 
 * author: James Smith, codefiend@gmail.com
 * 
 * description: This library contains a very simple state machine to be used with button-like
 *              inputs for Arduino projects.
 * 
 * usage: Declare a buttonState structure in your code and pass it to the desired update
 *        function. Digital reads from digital pins, Analog reads from analog pins. The Inv
 *        functions have an inverted effect (Pressed happens when pin state = LOW). Analog
 *        requires a trigger threshold, when the analogPin reads above this trigger level,
 *        the button will trigger.
 * 
 *        updateDigitalButton    - Digital input activated when closing a circuit
 *        updateInvDigitalButton - Digital input activated when opening a circuit
 *        updateAnalogButton     - Analog input activated when analog source >= threshold
 *        updateInvAnalogButton  - Analog input activated when analog source <= threshold
 * 
 *        All functions take the address of a buttonState structure as their first argument,
 *        and a pin to test as their second argument. The analog functions take a threshold
 *        as their third argument.
 * 
 * example:
 *   #include "buttonStates.h"
 *   int buttonPin = 2;
 *   struct buttonState button;
 * 
 *   void setup()
 *   {
 *     pinMode( buttonPin, INPUT );
 *   }
 * 
 *   void loop()
 *   {
 *     updateDigitalButton( &button, buttonPin );
 *     if( button.Pressed )
 *     {
 *       ...
 *     }
 *   }
 */
 
typedef struct buttonState
{
  bool Pressed;
  bool Held;
};

void updateDigitalButton( struct buttonState* state, int buttonPin )
{
  int pinState = digitalRead( buttonPin );
  if( state->Pressed == false && state->Held == false && pinState == HIGH )
  {
    state->Pressed = true;
  }
  else if( state->Pressed == true && state->Held == false && pinState == HIGH )
  {
    state->Pressed = false;
    state->Held = true;
  }
  else if( pinState == LOW )
  {
    state->Pressed = false;
    state->Held = false;
  }
}

void updateInvDigitalButton( struct buttonState* state, int buttonPin )
{
  int pinState = digitalRead( buttonPin );
  if( state->Pressed == false && state->Held == false && pinState == LOW )
  {
    state->Pressed = true;
  }
  else if( state->Pressed == true && state->Held == false && pinState == LOW )
  {
    state->Pressed = false;
    state->Held = true;
  }
  else if( pinState == HIGH )
  {
    state->Pressed = false;
    state->Held = false;
  }
}

void updateAnalogButton( struct buttonState* state, int buttonPin, int threshold )
{
  int pinState = analogRead( buttonPin );
  if( state->Pressed == false && state->Held == false && pinState >= threshold )
  {
    state->Pressed = true;
  }
  else if( state->Pressed == true && state->Held == false && pinState >= threshold )
  {
    state->Pressed = false;
    state->Held = true;
  }
  else if( pinState < threshold )
  {
    state->Pressed = false;
    state->Held = false;
  }
}

void updateInvAnalogButton( struct buttonState* state, int buttonPin, int threshold )
{
  int pinState = analogRead( buttonPin );
  if( state->Pressed == false && state->Held == false && pinState <= threshold )
  {
    state->Pressed = true;
  }
  else if( state->Pressed == true && state->Held == false && pinState <= threshold )
  {
    state->Pressed = false;
    state->Held = true;
  }
  else if( pinState > threshold )
  {
    state->Pressed = false;
    state->Held = false;
  }
}

#endif
