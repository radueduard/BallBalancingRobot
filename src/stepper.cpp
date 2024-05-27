#include "stepper.h"

StepperController::StepperController(PID* pidX, PID* pidY) :
    stepperX(AccelStepper::DRIVER, STEPPER_STEP_X, STEPPER_DIR_X),
    stepperA(AccelStepper::DRIVER, STEPPER_STEP_A, STEPPER_DIR_A),
    pidX(pidX),
    stepperY(AccelStepper::DRIVER, STEPPER_STEP_Y, STEPPER_DIR_Y),
    stepperZ(AccelStepper::DRIVER, STEPPER_STEP_Z, STEPPER_DIR_Z),
    pidY(pidY)
{
    pinMode(EN, OUTPUT);
    digitalWrite(EN, LOW);

    stepperX.setMaxSpeed(2000);
    stepperX.setAcceleration(10000);
    stepperX.setCurrentPosition(0);

    stepperY.setMaxSpeed(2000);
    stepperY.setAcceleration(10000);
    stepperY.setCurrentPosition(0);

    stepperZ.setMaxSpeed(2000);
    stepperZ.setAcceleration(10000);
    stepperZ.setCurrentPosition(0);

    stepperA.setMaxSpeed(2000);
    stepperA.setAcceleration(10000);
    stepperA.setCurrentPosition(0);

    stepperX.moveTo(300);
    stepperY.moveTo(300);
    stepperZ.moveTo(300);
    stepperA.moveTo(300);

    moveToTarget();
}

void StepperController::moveToTarget() {
    while (
        stepperX.distanceToGo() != 0 ||
        stepperY.distanceToGo() != 0 ||
        stepperZ.distanceToGo() != 0 ||
        stepperA.distanceToGo() != 0)
    {
        stepperX.run();
        stepperY.run();
        stepperZ.run();
        stepperA.run();
    }
}

void StepperController::setOXTarget() {
    int pos = pidX->get_value() * 200;
    int acc = 8000 * ((pos / 400.0) + 0.5) + 2000;

    stepperY.setAcceleration(acc);
    stepperZ.setAcceleration(acc);

    stepperY.moveTo(300 - pos);
    stepperZ.moveTo(300 + pos);
}

void StepperController::setOYTarget() {
    int pos = pidY->get_value() * 200;
    int acc = 8000 * ((pos / 400.0) + 0.5) + 2000;

    stepperX.setAcceleration(acc);
    stepperA.setAcceleration(acc);

    stepperX.moveTo(300 + pos);
    stepperA.moveTo(300 - pos);
}

void StepperController::run() {
    stepperX.run();
    stepperY.run();
    stepperZ.run();
    stepperA.run();
}

void StepperController::resetPIDS() {
    pidX->reset();
    pidY->reset();

    setOXTarget();
    setOYTarget();
}
