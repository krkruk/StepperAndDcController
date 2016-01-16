#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <QObject>

class StepperMotor
{
    QString positionInStepsKey;
    QString resetPositionKey;
    QString stepperModeKey;
    QString timeIntervalKey;

    int positionInStepsValue {0};
    bool resetPositionValue {false};
    short stepperModeValue {0};
    int timeIntervalValueMs {10};

    double angleToStepDeg {1.0};
    double gearRatio {1.0};

public:
    StepperMotor(int index);
    StepperMotor(const StepperMotor &other);
    StepperMotor(StepperMotor &&move);
    StepperMotor &operator=(const StepperMotor &other);
    enum DIRECTION {Clockwise, Counterclockwise};
};

#endif // STEPPERMOTOR_H
