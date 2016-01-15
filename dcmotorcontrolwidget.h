#ifndef DCMOTORCONTROLWIDGET_H
#define DCMOTORCONTROLWIDGET_H

#include <QWidget>

namespace Ui {
class DCMotorControlWidget;
}

class DCMotorControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DCMotorControlWidget(QWidget *parent = 0);
    ~DCMotorControlWidget();

    void setSliderEnabled(bool enable);
    double getFeedback() const;
    int getSliderValue() const;

signals:
    void dcMotorUpdated(int value);

public slots:
    void setFeedback(double feedbackValue);

private slots:
    void on_horizontalSliderDCPowerControl_actionTriggered(int action);

private:
    Ui::DCMotorControlWidget *ui;
};

#endif // DCMOTORCONTROLWIDGET_H
