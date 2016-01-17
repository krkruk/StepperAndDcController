#include "stepperwidgetcontroller.h"

StepperWidgetController::StepperWidgetController(
        QTabWidget *tabWidget, QObject *parent)
    : QObject(parent), tabWidget(tabWidget)
{
}

StepperWidgetController::~StepperWidgetController()
{
}

void StepperWidgetController::addTab(const QString &label)
{
    auto elemID = tabObjects.length() + startAtValue;
    tabObjects.append(std::shared_ptr<StepperControlWidget>{
                          new StepperControlWidget(elemID)
                      });

    stepperMotorsStates.append(std::move(StepperMotor(elemID)));
    auto *tabObj = tabObjects.last().get();
    tabWidget->addTab(tabObj, label);
    connect(tabObj, SIGNAL(stepperUpdated(int)), this, SLOT(onStepperUpdated(int)));
}

void StepperWidgetController::setSlidersEnabled(bool enable)
{
    for(auto &tab : tabObjects)
        tab->setSliderEnabled(enable);
}

bool StepperWidgetController::startInternalEnumerationAt(unsigned int startAt)
{
    if(tabObjects.length() == 0)
    {
        startAtValue = startAt;
        return true;
    }
    else return false;
}

unsigned int StepperWidgetController::getStartInternalEnumerationAt() const
{
    return startAtValue;
}

QList<StepperMotor> StepperWidgetController::getStepperMotorsStates() const
{
    return stepperMotorsStates;
}

std::shared_ptr<StepperSettingsDialog> StepperWidgetController::createSettingsDialog()
{
    auto maxElem = tabObjects.length() >= stepperMotorsStates.length() ?
                stepperMotorsStates.length() : tabObjects.length();
    auto stepperSettingsDialog = std::shared_ptr<StepperSettingsDialog>{
            new StepperSettingsDialog(&stepperMotorsStates)};

    for(int i = 0; i < maxElem; i++)
    {
        auto tabName = tabWidget->tabText(i);
        stepperSettingsDialog->addTab(tabName);
    }
    return stepperSettingsDialog;
}

void StepperWidgetController::onStepperUpdated(int stepperValue)
{
    auto *stepperSlider = qobject_cast<StepperControlWidget *>(sender());
    auto stepperID = stepperSlider->getId() - startAtValue;
    stepperMotorsStates[stepperID].setPositionInDeg(stepperValue);
    qDebug() << "Stepper #"<<stepperSlider->getId()
             << "Deg:"<<stepperMotorsStates[stepperID].getPositionInDeg()
             << "Steps:"<<stepperMotorsStates[stepperID].getPositionInSteps();

    emit stepperUpdate(stepperID);
}
