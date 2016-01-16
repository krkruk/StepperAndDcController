#include "steppersettingsdialog.h"
#include "ui_steppersettingsdialog.h"
#include "steppermotor.h"
#include <QMessageBox>
#include <QDebug>


void StepperSettingsDialog::setWidgetData(int index, StepperSettingsWidget *widget)
{
    if(stepperMotorsStates->length() > index)
    {
        widget->setAngleToStep(stepperMotorsStates->at(index).getAngleToStepDeg());
        widget->setGearRatio(stepperMotorsStates->at(index).getGearRatio());
        widget->setStepperMode(stepperMotorsStates->at(index).getStepperMode());
        widget->setTimeIntervalMs(stepperMotorsStates->at(index).getIntervalMs());
    }
}

StepperSettingsDialog::StepperSettingsDialog(QList<StepperMotor> *stepperMotorsStates, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::StepperSettingsDialog),
    stepperMotorsStates(stepperMotorsStates)
{
    ui->setupUi(this);
    this->setModal(true);
}

StepperSettingsDialog::~StepperSettingsDialog()
{
    delete ui;
}

void StepperSettingsDialog::addTab(const QString &label)
{
    settingsWidgets.append(std::shared_ptr<StepperSettingsWidget>{
                               new StepperSettingsWidget()
                           });
    auto *lastTab = settingsWidgets.last().get();
    ui->tabWidgetStepperSettings->addTab(lastTab, label);
    auto lastIndex = settingsWidgets.length() - 1;
    setWidgetData(lastIndex, lastTab);
}

void StepperSettingsDialog::on_buttonBox_accepted()
{
    int index = 0;
    for(auto &widget : settingsWidgets)
    {
        (*stepperMotorsStates)[index].setAngleToStepDeg(
                    widget->getAngleToStep());
        (*stepperMotorsStates)[index].setGearRatio(
                    widget->getGearRatio());
        (*stepperMotorsStates)[index].setStepperMode(
                    static_cast<StepperMotor::MODE>(
                        widget->getStepperMode()));
        (*stepperMotorsStates)[index].setIntervalMs(
                    widget->getTimeIntervalMs());
        ++index;
    }
}

void StepperSettingsDialog::on_buttonBox_rejected()
{
    QMessageBox::information(this, tr("Stepper settings"),
                             tr("No settings have been changed."));
}
