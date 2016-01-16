#include "steppersettingswidget.h"
#include "ui_steppersettingswidget.h"

StepperSettingsWidget::StepperSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StepperSettingsWidget),
    doubleValidator(0, 10000, 4, this),
    intValidator(0, 10000, this),
    localePreferences(locale())
{
    ui->setupUi(this);
    ui->lineEditAngleToStepDeg->setValidator(&doubleValidator);
    ui->lineEditGearRatio->setValidator(&doubleValidator);
    ui->lineEditTimeIntervalMs->setValidator(&intValidator);
}

StepperSettingsWidget::~StepperSettingsWidget()
{
    delete ui;
}

double StepperSettingsWidget::getAngleToStep()
{
    auto angleToStep = ui->lineEditAngleToStepDeg->text();
    return localePreferences.toDouble(angleToStep);
}

void StepperSettingsWidget::setAngleToStep(double angleToStep)
{
    ui->lineEditAngleToStepDeg->setText(localePreferences.toString(angleToStep));
}

double StepperSettingsWidget::getGearRatio()
{
    auto gear = ui->lineEditGearRatio->text();
    return localePreferences.toDouble(gear);
}

void StepperSettingsWidget::setGearRatio(double gear)
{
    ui->lineEditGearRatio->setText(localePreferences.toString(gear));
}

void StepperSettingsWidget::setStepperMode(short mode)
{
    switch(mode)
    {
    case HalfStep:
        ui->comboBoxModeSelect->setCurrentIndex(HalfStep);
        break;
    case FullStep:
    default:
        ui->comboBoxModeSelect->setCurrentIndex(FullStep);
    }
}

short StepperSettingsWidget::getStepperMode()
{
    auto mode = ui->comboBoxModeSelect->currentIndex();
    return mode;
}

void StepperSettingsWidget::setTimeIntervalMs(int timeInterval)
{
    ui->lineEditTimeIntervalMs->setText(localePreferences.toString(timeInterval));
}

int StepperSettingsWidget::getTimeIntervalMs()
{
    auto timeIntervalMs = ui->lineEditTimeIntervalMs->text().toInt();
    return timeIntervalMs;
}
