#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QSerialPortInfo>

#include "consts.h"
#include "StepperMotor/steppercontrolwidget.h"
#include "StepperMotor/steppersettingsdialog.h"
#include "DCMotor/dcmotorcontrolwidget.h"

#include "DCMotor/dcmotorwidgetcontroller.h"
#include "StepperMotor/stepperwidgetcontroller.h"
#include "serialport.h"

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

    void updateUartDevices();
    void connects();
    void openSerialConnection();
    void setStatusBarMsg(int time, const QString &str);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void enableSerialWidgets();
    void disableSerialWidgets();
    void setSerialMsgToSend(const QJsonObject &json);
    void readSerialLine(const QByteArray &line);
    void on_pushButtonUartReload_clicked();

    void on_pushButtonUartConnect_clicked();

    void on_action_Exit_triggered();

    void on_action_Author_triggered();

    void on_action_About_Qt_triggered();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<StepperSettingsDialog> stepperSettingsDialog;

    DCMotorWidgetController *dcMotorController;
    StepperWidgetController *stepperController;

    SerialPort *serial;
};

#endif // MAINWINDOW_H
