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

private:
    Ui::DCMotorControlWidget *ui;
};

#endif // DCMOTORCONTROLWIDGET_H
