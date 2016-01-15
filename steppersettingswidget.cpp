#include "steppersettingswidget.h"
#include "ui_steppersettingswidget.h"

StepperSettingsWidget::StepperSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StepperSettingsWidget)
{
    ui->setupUi(this);
}

StepperSettingsWidget::~StepperSettingsWidget()
{
    delete ui;
}
