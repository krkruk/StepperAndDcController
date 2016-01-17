#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <QObject>
#include <QSettings>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>

class StepperMotor
{
    QString positionInStepsKey;
    QString resetPositionKey;
    QString stepperModeKey;
    QString timeIntervalKey;

    int positionInStepsValue {0};
    double positionInDeg {0.0};
    bool resetPositionValue {false};
    short stepperModeValue {0};
    int timeIntervalValueMs {10};

    double angleToStepDeg {1.0};
    double gearRatio {1.0};

    double lowerStepLimit {1.0};
    double upperStepLimit {1.0};

    int positionInStepsFeedback {0};
    double positionInDegFeedback {0.0};
    bool resetPositionFeedback {false};
    short stepperModeFeedback {0};
    int timeIntervalFeedbackMs {10};

public:
    StepperMotor(int index);
    StepperMotor(const StepperMotor &other);
    StepperMotor(StepperMotor &&move);
    StepperMotor &operator=(const StepperMotor &other);
    ~StepperMotor();
    enum MODE {FullStep, HalfStep};

    void setPositionInSteps(int steps);
    int getPositionInSteps() const;

    void setPositionInDeg(double degrees);
    double getPositionInDeg() const;

    void setResetPosition(bool reset);
    bool getResetPosition();

    void setStepperMode(enum MODE mode);
    short getStepperMode() const;

    void setIntervalMs(int timeIntervalMs);
    int getIntervalMs() const;

    double getAngleToStepDeg() const;
    void setAngleToStepDeg(double angleToStep);

    double getGearRatio() const;
    void setGearRatio(double gear);

    QString getPositionInStepsKey() const;
    QString getResetPositionKey() const;
    QString getStepperModeKey() const;
    QString getTimeIntervalKey() const;

    void updateStepsPerRevolution();
    double calculateCurrentAngle(int positionInSteps) const;
    int calculateCurrentSteps();

    QJsonObject getPositionInStepsJson();
    QJsonObject getResetPositionJson();
    QJsonObject getStepperModeJson();
    QJsonObject getTimeIntervalJson();

    QJsonObject getJson();

    int getPositionInStepsFeedback() const;
    bool getResetPositionFeedback() const;
    short getStepperModeFeedback() const;
    int getTimeIntervalFeedbackMs() const;
    double getPositionInDegFeedback() const;

    void parseJson(const QByteArray &jsonArray);

private:
    void loadSettings();
    void saveSettings();
};

#endif // STEPPERMOTOR_H
