#ifndef DCMOTOR_H
#define DCMOTOR_H

#include <QObject>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>

class DCMotor
{
    QString pwmKey;
    QString directionKey;

    unsigned short pwmValue {0};
    unsigned short dirn {0};

    unsigned short pwmFeedback {0};
    unsigned short dirnFeedback {0};

public:
    DCMotor(int index);
    DCMotor(const DCMotor &other);
    DCMotor(DCMotor &&move);
    DCMotor &operator=(const DCMotor &other);


    enum DIRECTION { Clockwise, Counterclockwise };

    void setPwm(int pwm);
    unsigned short getPwm() const;

    void setDirection(enum DIRECTION dirn);
    unsigned short getDirection() const;

    QJsonObject getPwmJson();
    QJsonObject getDirectionJson();
    QJsonObject getJson();

    void parseJson(const QByteArray &jsonArray);
    unsigned short getPwmFeedback() const;
    unsigned short getDirnFeedback() const;
};

#endif // DCMOTOR_H
