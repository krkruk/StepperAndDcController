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
    explicit StepperControlWidget(QWidget *parent = 0);
    ~StepperControlWidget();

private:
    Ui::StepperControlWidget *ui;
};

#endif // STEPPERCONTROLWIDGET_H
