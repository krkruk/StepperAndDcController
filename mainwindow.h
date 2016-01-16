#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>

#include "steppercontrolwidget.h"
#include "steppersettingsdialog.h"
#include "dcmotorcontrolwidget.h"

#include "dcmotorwidgetcontroller.h"
/*
     * s1 - stepper 1, position in steps
     * s2 - stepper 2, position in steps
     * sr1 - stepper 1 reset position [0..1],
     * sr2 - stepper 2 reset position [0..1],
     * sm1 - stepper 1, mode: 0 - full step, 1 - half step
     * sm2 - stepper 2, mode: 0 - full step, 1 - half step
     * st1 - stepper1, time interval in ms
     * st2 - stepper2, time interval in ms
     * p1 - dc motor 1, pwm [0..100]
     * d1 - dc motor 1, direction [0..1]; 0 - clockwise, 1, counterclockwise
     * p2 - dc motor 2, pwm [0..100]
     * d2 - dc motor 2, direction [0..1]
     * *1 - left
     * *2 - right
     */
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;
    StepperSettingsDialog *stepperSettingsDialog;

    StepperControlWidget *stepper1;

    DCMotorWidgetController *dcMotorController;
};

#endif // MAINWINDOW_H
