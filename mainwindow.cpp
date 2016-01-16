#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stepperSettingsDialog = new StepperSettingsDialog(this);
    stepper1 = new StepperControlWidget(this);
    dcMotorController = new DCMotorWidgetController(
                ui->tabWidgetDCMotorSelect, this);

    ui->tabWidgetStepperSelect->addTab(stepper1, "Stepper1");
    dcMotorController->addTab("Motor 1");
    dcMotorController->addTab("Motor 2");
    dcMotorController->setSlidersEnabled(true);

    connect(ui->actionStepper, SIGNAL(triggered(bool)), stepperSettingsDialog, SLOT(show()));
}

MainWindow::~MainWindow()
{
    delete dcMotorController;
    delete stepper1;
    delete stepperSettingsDialog;
    delete ui;
}

