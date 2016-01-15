#include "steppercontrolwidget.h"
#include "ui_steppercontrolwidget.h"

StepperControlWidget::StepperControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StepperControlWidget)
{
    ui->setupUi(this);
}

StepperControlWidget::~StepperControlWidget()
{
    delete ui;
}
