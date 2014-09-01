#ifndef _BUTTONSTATES_H_
#define _BUTTONSTATES_H_

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
