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

void StepperWidgetController::reset()
{
    for(auto &tab : tabObjects)
        tab->reset();
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

int StepperWidgetController::getLastElemUpdatedIndex() const
{
    return lastElemUpdatedIndex;
}

QJsonObject StepperWidgetController::getLastJson()
{
    auto json = stepperMotorsStates[lastElemUpdatedIndex].getJson();
    return json;
}

void StepperWidgetController::stepperUpdateFeedback(const QString &json)
{
    for(auto &state : stepperMotorsStates)
        state.parseJson(json);

    int index = 0;
    for(auto &tab : tabObjects)
    {
        auto stepperPosInDeg =
                stepperMotorsStates.at(index).getPositionInDegFeedback();
        tab->setFeedback(stepperPosInDeg);
        ++index;
    }
}

void StepperWidgetController::onStepperUpdated(int stepperValue)
{
    auto *stepperSlider = qobject_cast<StepperControlWidget *>(sender());
    lastElemUpdatedIndex = stepperSlider->getId() - startAtValue;
    stepperMotorsStates[lastElemUpdatedIndex].setPositionInDeg(stepperValue);

    emit stepperUpdate(lastElemUpdatedIndex);
    emit stepperJsonUpdate(stepperMotorsStates[lastElemUpdatedIndex].getJson());
}
