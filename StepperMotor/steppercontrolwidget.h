#ifndef STEPPERCONTROLWIDGET_H
#define STEPPERCONTROLWIDGET_H

#include <QWidget>

namespace Ui {
class StepperControlWidget;
}

class StepperControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StepperControlWidget(unsigned int id, QWidget *parent = 0);
    ~StepperControlWidget();

    void setSliderEnabled(bool enable);
    double getFeedback() const;
    int getSliderValue() const;
    unsigned int getId() const;
    void reset();

signals:
    void stepperUpdated(int value);

public slots:
    void setFeedback(double feedbackValue);

private slots:
    void on_horizontalSliderStepperPositionInDeg_actionTriggered(int action);

private:
    Ui::StepperControlWidget *ui;
    unsigned int id {0};
};

#endif // STEPPERCONTROLWIDGET_H
