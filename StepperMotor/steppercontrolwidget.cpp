#include "steppercontrolwidget.h"
#include "ui_steppercontrolwidget.h"

StepperControlWidget::StepperControlWidget(unsigned int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StepperControlWidget), id(id)
{
    ui->setupUi(this);
    ui->lineEditStepperFeedbackInDeg->setReadOnly(true);
    ui->lineEditStepperSliderPositionInDeg->setReadOnly(true);
}

StepperControlWidget::~StepperControlWidget()
{
    delete ui;
}

void StepperControlWidget::setSliderEnabled(bool enable)
{
    ui->horizontalSliderStepperPositionInDeg->setEnabled(enable);
    if(enable)
    {
        int middle = (ui->horizontalSliderStepperPositionInDeg->minimum()
                + ui->horizontalSliderStepperPositionInDeg->maximum()) * 0.5;
        ui->horizontalSliderStepperPositionInDeg->setValue(middle);
    }
}

double StepperControlWidget::getFeedback() const
{
    return ui->lineEditStepperFeedbackInDeg->text().toDouble();
}

int StepperControlWidget::getSliderValue() const
{
    return ui->horizontalSliderStepperPositionInDeg->value();
}

unsigned int StepperControlWidget::getId() const
{
    return id;
}

void StepperControlWidget::setFeedback(double feedbackValue)
{
    ui->lineEditStepperFeedbackInDeg->setText(QString::number(feedbackValue));
}

void StepperControlWidget::on_horizontalSliderStepperPositionInDeg_actionTriggered(int action)
{
    auto sliderValue = ui->horizontalSliderStepperPositionInDeg->value();

    ui->lineEditStepperSliderPositionInDeg->setText(QString::number(sliderValue));
    emit stepperUpdated(sliderValue);
    Q_UNUSED(action)
}
