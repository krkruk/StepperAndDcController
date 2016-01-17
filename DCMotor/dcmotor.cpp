#include "dcmotor.h"
#include <memory>
#include <cmath>


DCMotor::DCMotor(int index)
    : pwmKey(QString("p%1").arg(index)),
      directionKey(QString("d%1").arg(index))
{}

DCMotor::DCMotor(const DCMotor &other)
{
    *this = other;
}

DCMotor::DCMotor(DCMotor &&move)
    : pwmKey(std::move(move.pwmKey)),
      directionKey(std::move(move.directionKey)),
      pwmValue(std::move(move.pwmValue)),
      dirn(std::move(move.dirn))
{}

DCMotor &DCMotor::operator=(const DCMotor &other)
{
    pwmKey = other.pwmKey;
    directionKey = other.directionKey;
    pwmValue = other.pwmValue;
    dirn = other.dirn;
    return *this;
}


/*!
 * \brief DCMotor::setPwm Set pwm in range [-255, 255]
 * \param pwm value between [-255, 255]
 *
 * Set PWM for the device. If the value < 0, the motor
 * will rotate counterclockwise, otherwise clockwise.
 * No need to use setDirection separately.
 */
void DCMotor::setPwm(int pwm)
{
    dirn = pwm >= 0 ? Clockwise : Counterclockwise;
    pwmValue = abs(pwm);
}

/*!
 * \brief DCMotor::getPwm Gets PWM in range [0, 255]
 * \return unsigned short
 *
 * Get pure PWM value. If direction is needed still have
 * to call getDirection() const;
 */
unsigned short DCMotor::getPwm() const
{
    return pwmValue;
}

void DCMotor::setDirection(DCMotor::DIRECTION dirn)
{
    this->dirn = dirn;
}

unsigned short DCMotor::getDirection() const
{
    return dirn;
}

QJsonObject DCMotor::getPwmJson()
{
    QJsonValue jsonPWM(pwmValue);
    return QJsonObject({
                           QPair<QString, QJsonValue>(pwmKey, jsonPWM)
                       });
}

QJsonObject DCMotor::getDirectionJson()
{
    QJsonValue jsonDir(dirn);
    return QJsonObject({
                           QPair<QString, QJsonValue>(directionKey, jsonDir)
                       });
}

QJsonObject DCMotor::getJson()
{
    QJsonValue jsonPWM(pwmValue);
    QJsonValue jsonDir(dirn);
    return QJsonObject({
                           QPair<QString, QJsonValue>(pwmKey, jsonPWM),
                           QPair<QString, QJsonValue>(directionKey, jsonDir)
                       });
}

void DCMotor::parseJson(const QString &jsonString)
{
    auto json = QJsonDocument::fromJson(jsonString.toLatin1());
    auto jsonObj = json.object();

    pwmFeedback = jsonObj.value(pwmKey).toInt(pwmFeedback);
    dirnFeedback = jsonObj.value(directionKey).toInt(pwmFeedback);
}

unsigned short DCMotor::getPwmFeedback() const
{
    return pwmFeedback;
}

unsigned short DCMotor::getDirnFeedback() const
{
    return dirnFeedback;
}
