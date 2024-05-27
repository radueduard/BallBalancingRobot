#pragma once

#include <Arduino.h>
#include <AccelStepper.h>
#include "pid.h"

#define STEPPER_STEP_X 2
#define STEPPER_DIR_X 5

#define STEPPER_STEP_Y 3
#define STEPPER_DIR_Y 6

#define STEPPER_STEP_Z 4
#define STEPPER_DIR_Z 7

#define STEPPER_STEP_A A4
#define STEPPER_DIR_A A5

#define EN 8

class StepperController {
public:
    StepperController(PID* pidX, PID* pidY);
    void moveToTarget();
    void setOXTarget();
    void setOYTarget();
    void run();
    void resetPIDS();
private:
    AccelStepper stepperX;
    AccelStepper stepperA;
    PID* pidX;

    AccelStepper stepperY;
    AccelStepper stepperZ;
    PID* pidY;
};