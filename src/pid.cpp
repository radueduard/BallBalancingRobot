#include "pid.h"
#include <Arduino.h>

PID::PID(float kP, float kI, float kD, float target) : kP(kP), kI(kI), kD(kD), target(target) {
    proportional = 0;
    integral = 0;
    derivative = 0;
}

void PID::set_target(int target) {
    this->target = target;

    this->proportional = 0;
    this->integral = 0;
    this->derivative = 0;
}

void PID::update(int current) {
    lastError = proportional;
    proportional = OFFSET - current - target;
    integral += proportional + lastError;
    derivative = proportional - lastError;
    derivative = isnan(derivative) || isinf(derivative) ? 0 : derivative;
}

float PID::get_value() {
    return constrain(kP * proportional + kI * integral + kD * derivative, -0.25, 0.25);
}

void PID::reset() {
    proportional = 0;
    integral = 0;
    derivative = 0;
}