#ifndef DCMOTOR_H
#define DCMOTOR_H

#include <QObject>

class DCMotor
{
    QString pwmKey;
    QString directionKey;

    unsigned short pwmValue {0};
    unsigned short dirn {0};
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
};

#endif // DCMOTOR_H
