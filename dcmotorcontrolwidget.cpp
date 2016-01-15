#include "dcmotorcontrolwidget.h"
#include "ui_dcmotorcontrolwidget.h"

DCMotorControlWidget::DCMotorControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DCMotorControlWidget)
{
    ui->setupUi(this);
}

DCMotorControlWidget::~DCMotorControlWidget()
{
    delete ui;
}
