#include <Arduino.h>
#include "stepper.h"

#include <TouchScreen.h>

#include "pid.h"

PID* pidX;
PID* pidY;
StepperController* controller;
TouchScreen* touchscreen;

uint16_t ox = 0;
uint16_t oy = 0;

#define KP 4E-4     
#define KI 2E-6
#define KD 7E-3

volatile bool read = false;

ISR(TIMER1_COMPA_vect) {
  read = true;
}

void initTimer() {
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 4999;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS11) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  initTimer();
  sei();

  touchscreen = new TouchScreen(A3, A2, A1, A0, 0);
  pidX = new PID(KP, KI, KD, 0);
  pidY = new PID(KP, KI, KD, 0);
  controller = new StepperController(pidX, pidY);
}

void loop() {
  if (read) {
    read = false;
    TSPoint p = touchscreen->getPoint();
    if (p.x != 0) {
      pidX->update(1023 - p.y);
      pidY->update(1023 - p.x);
    }
    else {
      p = touchscreen->getPoint();
      if (p.x != 0) {
        pidX->update(1023 - p.y);
        pidY->update(1023 - p.x);
      }
      else {
        controller->resetPIDS();
      }
    }

    controller->setOXTarget();
    controller->setOYTarget();
  }
  controller->run();
}