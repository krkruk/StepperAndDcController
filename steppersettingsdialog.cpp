#include "steppersettingsdialog.h"
#include "ui_steppersettingsdialog.h"

StepperSettingsDialog::StepperSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StepperSettingsDialog)
{
    ui->setupUi(this);
    stepper1 = new StepperSettingsWidget(this);
    ui->tabWidgetStepperSettings->addTab(stepper1, "Stepper 1");
}

StepperSettingsDialog::~StepperSettingsDialog()
{
    delete stepper1;
    delete ui;
}
