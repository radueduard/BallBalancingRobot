#pragma once

#include <stdint.h>

#define OFFSET 510

class PID {
public:
    PID(float kP, float kI, float kD, float target);
    void set_target(int target);
    void update(int current);
    float get_value();
    void reset();
private:
    float kP;
    float kI;
    float kD;

    float target;

    float lastError;
    float proportional;
    float integral;
    float derivative;
};