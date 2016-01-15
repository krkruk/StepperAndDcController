#include "dcmotorcontrolwidget.h"
#include "ui_dcmotorcontrolwidget.h"

DCMotorControlWidget::DCMotorControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DCMotorControlWidget)
{
    ui->setupUi(this);

    ui->lineEditDCMotorFeedbackValue->setReadOnly(true);
    ui->lineEditDCMotorSliderValue->setReadOnly(true);
    ui->horizontalSliderDCPowerControl->setEnabled(false);
}

DCMotorControlWidget::~DCMotorControlWidget()
{
    delete ui;
}

void DCMotorControlWidget::setSliderEnabled(bool enable)
{
    ui->horizontalSliderDCPowerControl->setEnabled(enable);
    if(enable)
    {
        int middle = (ui->horizontalSliderDCPowerControl->minimum()
                + ui->horizontalSliderDCPowerControl->maximum()) * 0.5;
        ui->horizontalSliderDCPowerControl->setValue(middle);
    }
}

double DCMotorControlWidget::getFeedback() const
{
    return ui->lineEditDCMotorFeedbackValue->text().toDouble();
}

int DCMotorControlWidget::getSliderValue() const
{
    return ui->horizontalSliderDCPowerControl->value();
}

void DCMotorControlWidget::setFeedback(double feedbackValue)
{
    ui->lineEditDCMotorFeedbackValue->setText(QString::number(feedbackValue));
}

void DCMotorControlWidget::on_horizontalSliderDCPowerControl_actionTriggered(int action)
{
    auto sliderValue = ui->horizontalSliderDCPowerControl->value();

    ui->lineEditDCMotorSliderValue->setText(QString::number(sliderValue));
    emit dcMotorUpdated(sliderValue);
    Q_UNUSED(action)
}
