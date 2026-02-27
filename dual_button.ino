/*****************************************
* Project: Simultaneous Dual-Button LED Activation with Hardware & Software Debounce
* Author: Ali-Sbeity
* Version: 1.0
* Copyright (c) 2026 Ali-Sbeity
* License: MIT License
********************************/

// --- Configuration ---

const int button1Pin = 2;
const int button2Pin = 3;
const int ledPin     = 13;

const unsigned long debounceDelay = 50;
const unsigned long timerDuration = 5000;


// --- Debounce Structure ---


struct Button {
  int pin;
  int lastReading;
  int stableState;
  unsigned long lastDebounceTime;
};

Button button1 = {button1Pin, HIGH, HIGH, 0};
Button button2 = {button2Pin, HIGH, HIGH, 0};


// --- FSM Definition ---


enum SystemState {
  IDLE,
  LED_ON,
  WAIT_RELEASE
};

SystemState currentState = IDLE;

unsigned long ledStartTime = 0;


// --- Setup ---


void setup() {
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}


// --- Debounce Function ---


void updateButton(Button &btn) {
  int reading = digitalRead(btn.pin);

  if (reading != btn.lastReading) {
    btn.lastDebounceTime = millis();
  }

  if ((millis() - btn.lastDebounceTime) > debounceDelay) {
    if (reading != btn.stableState) {
      btn.stableState = reading;
    }
  }

  btn.lastReading = reading;
}


// --- Main Loop ---


void loop() {

  updateButton(button1);
  updateButton(button2);

  switch (currentState) {

    case IDLE:

      if (button1.stableState == LOW &&
          button2.stableState == LOW) {

        digitalWrite(ledPin, HIGH);
        ledStartTime = millis();
        currentState = LED_ON;
      }
      break;


    case LED_ON:

      if (millis() - ledStartTime >= timerDuration) {
        digitalWrite(ledPin, LOW);
        currentState = WAIT_RELEASE;
      }
      break;


    case WAIT_RELEASE:

      if (button1.stableState == HIGH &&
          button2.stableState == HIGH) {

        currentState = IDLE;
      }
      break;
  }
}

// Copyright (c) 2026 Ali-Sbeity  
// License: MIT License
