#ifndef DCMOTORCONTROLWIDGET_H
#define DCMOTORCONTROLWIDGET_H

#include <QWidget>

namespace Ui {
class DCMotorControlWidget;
}

class DCMotorControlWidget : public QWidget
{
    Q_OBJECT

    double toPercent(double value);
public:
    explicit DCMotorControlWidget(unsigned int id, QWidget *parent = 0);
    ~DCMotorControlWidget();

    void setSliderEnabled(bool enable);
    double getFeedback() const;
    int getSliderValue() const;
    unsigned int getId() const;
    void reset();
signals:
    void dcMotorUpdated(int value);

public slots:
    void setFeedback(double feedbackValue);

private slots:
    void on_horizontalSliderDCPowerControl_actionTriggered(int action);

    void on_pushButtonEmergencyStop_clicked();

private:
    Ui::DCMotorControlWidget *ui;
    unsigned int id {0};
};

#endif // DCMOTORCONTROLWIDGET_H
