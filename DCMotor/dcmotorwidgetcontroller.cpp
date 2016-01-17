#include "dcmotorwidgetcontroller.h"
#include <QDebug>

DCMotorWidgetController::DCMotorWidgetController(
        QTabWidget *tabWidget, QObject *parent)
    : QObject(parent), tabWidget(tabWidget)
{
}

DCMotorWidgetController::~DCMotorWidgetController()
{}

void DCMotorWidgetController::addTab(const QString &label)
{
    auto elemID = tabObjects.length() + startAtValue;
    tabObjects.append(std::shared_ptr<DCMotorControlWidget>{
                          new DCMotorControlWidget(elemID)
                      });
    dcMotorsStates.append(DCMotor(elemID));
    auto *tabObj = tabObjects.last().get();
    tabWidget->addTab(tabObj, label);
    connect(tabObj, SIGNAL(dcMotorUpdated(int)), this, SLOT(onDcMotorUpdated(int)));
}

void DCMotorWidgetController::setSlidersEnabled(bool enable)
{
    for(auto &tab : tabObjects)
        tab->setSliderEnabled(enable);
}

void DCMotorWidgetController::reset()
{
    for(auto &tab : tabObjects)
        tab->reset();
}

bool DCMotorWidgetController::startInternalEnumerationAt(unsigned int startAt)
{
    if(tabObjects.length() == 0)
    {
        startAtValue = startAt;
        return true;
    }
    else return false;
}

unsigned int DCMotorWidgetController::getStartInternalEnumerationAt() const
{
    return startAtValue;
}

QList<DCMotor> DCMotorWidgetController::getDcMotorsStates() const
{
    return dcMotorsStates;
}

int DCMotorWidgetController::getLastElemUpdatedIndex() const
{
    return lastElemUpdatedIndex;
}

QJsonObject DCMotorWidgetController::getLastJson()
{
    auto json = dcMotorsStates[lastElemUpdatedIndex].getJson();
    return json;
}

void DCMotorWidgetController::dcMotorUpdateFeedback(const QByteArray &json)
{
    for(auto &state : dcMotorsStates)
        state.parseJson(json);

    int index = 0;
    for(auto &tab : tabObjects)
    {
        auto pwmFeedback = dcMotorsStates.at(index).getPwmFeedback();
        pwmFeedback = pwmFeedback > 0 ? pwmFeedback : -1*pwmFeedback;
        tab->setFeedback(pwmFeedback);
        ++index;
    }
}

void DCMotorWidgetController::onDcMotorUpdated(int dcValue)
{
    auto dcSlider = qobject_cast<DCMotorControlWidget *>(sender());
    lastElemUpdatedIndex = dcSlider->getId() - startAtValue;
    dcMotorsStates[lastElemUpdatedIndex].setPwm(dcValue);

    emit dcMotorUpdate(lastElemUpdatedIndex);
    emit dcMotorJsonUpdate(dcMotorsStates[lastElemUpdatedIndex].getJson());
}
