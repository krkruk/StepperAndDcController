#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>

#include "steppercontrolwidget.h"
#include "steppersettingsdialog.h"
#include "dcmotorcontrolwidget.h"

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
    DCMotorControlWidget *dc1;

};

#endif // MAINWINDOW_H
