/**
 * @file main.cpp
 * @author Christian Oertli (christian.oertli@aequator.ch)
 * @brief Tango brewer unit connected to a C14 machine. for stepper motor . ESPDUINO-32 with a sparkfun monster shield.
 * @version 0.1
 * @date 2021-06-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include <Arduino.h>
/*#include <Stepper.h>

/**
 * @brief constants won't change. They're used here to set pin numbers:
 * 
 */


const int BUTTON_PIN = 21;   /**
 * @brief  // GIOP21 pin connected to button
 * 
 */

const int DEBOUNCE_DELAY = 50; /**
 * @brief the debounce time; increase if the output flickers
 * 
 */

/**
 * @brief Variables will change:
 * 
 */
int lastSteadyState = LOW;       // the previous steady state from the input pin
int lastFlickerableState = LOW;  // the previous flickerable state from the input pin
int currentState;                // the current reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize the pushbutton pin as an pull-up input
  // the pull-up input pin will be HIGH when the switch is open and LOW when the switch is closed.
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // read the state of the switch/button:
  currentState = digitalRead(BUTTON_PIN);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch/button changed, due to noise or pressing:
  if (currentState != lastFlickerableState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastFlickerableState = currentState;
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if(lastSteadyState == HIGH && currentState == LOW){
      Serial.println("The button is pressed");
      Serial.println("Drainage on");}
    else if(lastSteadyState == LOW && currentState == HIGH){
      Serial.println("The button is released");
      Serial.println("Drainage off");
    }
      

    // save the the last steady state
    lastSteadyState = currentState;
  }
}