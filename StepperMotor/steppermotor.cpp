#include "steppermotor.h"
#include "consts.h"
#include <QPair>
#include <QDebug>
StepperMotor::StepperMotor(int index)
    : positionInStepsKey(QString("s%1").arg(index)),
      resetPositionKey(QString("sr%1").arg(index)),
      stepperModeKey(QString("sm%1").arg(index)),
    timeIntervalKey(QString("st%1").arg(index))
{
    loadSettings();
    updateStepsPerRevolution();
}

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
      positionInDeg(std::move(move.positionInDeg)),
      resetPositionValue(std::move(move.resetPositionValue)),
      stepperModeValue(std::move(move.stepperModeValue)),
      timeIntervalValueMs(std::move(move.timeIntervalValueMs)),
      angleToStepDeg(std::move(move.angleToStepDeg)),
      gearRatio(std::move(move.gearRatio))
{
    updateStepsPerRevolution();
}

StepperMotor &StepperMotor::operator=(const StepperMotor &other)
{
    positionInStepsKey = other.positionInStepsKey;
    resetPositionKey = other.resetPositionKey;
    stepperModeKey = other.stepperModeKey;
    timeIntervalKey = other.timeIntervalKey;

    positionInStepsValue = other.positionInStepsValue;
    positionInDeg = other.positionInDeg;
    resetPositionValue = other.resetPositionValue;
    stepperModeValue = other.stepperModeValue;
    timeIntervalValueMs = other.timeIntervalValueMs;

    angleToStepDeg = other.angleToStepDeg;
    gearRatio = other.gearRatio;
    updateStepsPerRevolution();
    return *this;
}

StepperMotor::~StepperMotor()
{
    saveSettings();
}

void StepperMotor::setPositionInSteps(int steps)
{
    positionInStepsValue = steps;
    positionInDeg = calculateCurrentAngle();
}

int StepperMotor::getPositionInSteps() const
{
    return positionInStepsValue;
}

void StepperMotor::setPositionInDeg(double degrees)
{
    positionInDeg = degrees;
    positionInStepsValue = calculateCurrentSteps();
}

double StepperMotor::getPositionInDeg() const
{
    return positionInDeg;
}

void StepperMotor::setResetPosition(bool reset)
{
    resetPositionValue = reset;
}

bool StepperMotor::getResetPosition()
{
    if(resetPositionValue)
    {
        resetPositionValue = false;
        return true;
    }
    else return false;
}

void StepperMotor::setStepperMode(MODE mode)
{
    stepperModeValue = mode;
    updateStepsPerRevolution();
}

short StepperMotor::getStepperMode() const
{
    return stepperModeValue;
}

void StepperMotor::setIntervalMs(int timeIntervalMs)
{
    timeIntervalValueMs = timeIntervalMs;
}

int StepperMotor::getIntervalMs() const
{
    return timeIntervalValueMs;
}

double StepperMotor::getAngleToStepDeg() const
{
    return angleToStepDeg;
}

void StepperMotor::setAngleToStepDeg(double angleToStep)
{
    if(angleToStep > 0)
    {
        angleToStepDeg = angleToStep;
        updateStepsPerRevolution();
    }
}

double StepperMotor::getGearRatio() const
{
    return gearRatio;
}

void StepperMotor::setGearRatio(double gear)
{
    if(gear > 0)
    {
        gearRatio = gear;
        updateStepsPerRevolution();
    }
}

QString StepperMotor::getPositionInStepsKey() const
{
    return positionInStepsKey;
}

QString StepperMotor::getResetPositionKey() const
{
    return resetPositionKey;
}

QString StepperMotor::getStepperModeKey() const
{
    return stepperModeKey;
}

QString StepperMotor::getTimeIntervalKey() const
{
    return timeIntervalKey;
}

void StepperMotor::loadSettings()
{
    QSettings settings(Consts::ORGANIZATION_NAME, Consts::ORGANIZATION_NAME);
    settings.beginGroup(Consts::STEPPERMOTOR_SETTINGS_GROUP);
    stepperModeValue = settings.value(stepperModeKey, FullStep).toInt();
    timeIntervalValueMs = settings.value(timeIntervalKey, 10).toInt();
    QString angleToStepDegKey = QString("%1AngleToStep").arg(stepperModeKey);
        angleToStepDeg = settings.value(angleToStepDegKey, 1.0).toDouble();
    QString gearRatioKey = QString("%1GearRatio").arg(stepperModeKey);
        gearRatio = settings.value(gearRatioKey, 1.0).toDouble();
    settings.endGroup();
}

void StepperMotor::saveSettings()
{
    QSettings settings(Consts::ORGANIZATION_NAME, Consts::ORGANIZATION_NAME);
    settings.beginGroup(Consts::STEPPERMOTOR_SETTINGS_GROUP);
    settings.setValue(stepperModeKey, stepperModeValue);
    settings.setValue(timeIntervalKey, timeIntervalValueMs);
    QString angleToStepDegKey = QString("%1AngleToStep").arg(stepperModeKey);
        settings.setValue(angleToStepDegKey, angleToStepDeg);
    QString gearRatioKey = QString("%1GearRatio").arg(stepperModeKey);
        settings.setValue(gearRatioKey, gearRatio);
    settings.endGroup();
}

void StepperMotor::updateStepsPerRevolution()
{
    short multiplier = (stepperModeValue == HalfStep) ? 2 : 1;
    lowerStepLimit = - (360.0f / angleToStepDeg) * gearRatio * multiplier;
    upperStepLimit = (360.0f / angleToStepDeg) * gearRatio * multiplier;
    qDebug() << "Lower:"<<lowerStepLimit <<"Upper:"<<upperStepLimit;
}

double StepperMotor::calculateCurrentAngle() const
{
    return 360 * positionInStepsValue / upperStepLimit;
}

int StepperMotor::calculateCurrentSteps()
{
    qDebug() << "posInDeg:"<<positionInDeg<<"upperLimit"<<upperStepLimit;
    return positionInDeg * upperStepLimit / 360.0f;
}
