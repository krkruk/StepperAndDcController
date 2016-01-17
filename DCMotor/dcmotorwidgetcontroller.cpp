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

void DCMotorWidgetController::onDcMotorUpdated(int dcValue)
{
    auto dcSlider = qobject_cast<DCMotorControlWidget *>(sender());
    auto dcID = dcSlider->getId() - startAtValue;
    dcMotorsStates[dcID].setPwm(dcValue);
    qDebug() << "DC value: " << dcMotorsStates.at(dcID).getPwm()
             << "Direction: "<< dcMotorsStates.at(dcID).getDirection()
             << "ID: " <<dcSlider->getId();

    emit dcMotorUpdate(dcID);
}
