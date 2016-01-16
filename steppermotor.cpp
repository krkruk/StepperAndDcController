#include "steppermotor.h"

StepperMotor::StepperMotor(int index)
    : positionInStepsKey(QString("s%1").arg(index)),
    resetPositionKey(QString("sr%1").arg(index)),
    stepperModeKey(QString("sm%1").arg(index)),
    timeIntervalKey(QString("st%1").arg(index))
{}

StepperMotor::StepperMotor(const StepperMotor &other)
{
    *this = other;
}

StepperMotor::StepperMotor(StepperMotor &&move)
    : positionInStepsKey(std::move(move.positionInStepsKey)),
      resetPositionKey(std::move(move.resetPositionKey)),
      stepperModeKey(std::move(move.stepperModeKey)),
      timeIntervalKey(std::move(move.timeIntervalKey)),
      positionInStepsValue(std::move(move.positionInStepsValue)),
      resetPositionValue(std::move(move.resetPositionValue)),
      stepperModeValue(std::move(move.stepperModeValue)),
      timeIntervalValueMs(std::move(move.timeIntervalValueMs))
{}

StepperMotor &StepperMotor::operator=(const StepperMotor &other)
{
    positionInStepsKey = other.positionInStepsKey;
    resetPositionKey = other.resetPositionKey;
    stepperModeKey = other.stepperModeKey;
    timeIntervalKey = other.timeIntervalKey;

    positionInStepsValue = other.positionInStepsValue;
    resetPositionValue = other.resetPositionValue;
    stepperModeValue = other.stepperModeValue;
    timeIntervalValueMs = other.timeIntervalValueMs;
}
