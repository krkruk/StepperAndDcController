#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dcMotorController = new DCMotorWidgetController(
                ui->tabWidgetDCMotorSelect, this);
    dcMotorController->startInternalEnumerationAt(1);
    dcMotorController->addTab(Consts::DCMOTOR1_LABEL);
    dcMotorController->addTab(Consts::DCMOTOR2_LABEL);
    dcMotorController->setSlidersEnabled(true);

    stepperController = new StepperWidgetController(
                ui->tabWidgetStepperSelect, this);
    stepperController->startInternalEnumerationAt(1);
    stepperController->addTab(Consts::STEPPER1_LABEL);
    stepperController->addTab(Consts::STEPPER2_LABEL);
    stepperController->setSlidersEnabled(true);

    stepperSettingsDialog = stepperController->createSettingsDialog();

    connect(ui->actionStepper, SIGNAL(triggered(bool)), stepperSettingsDialog.get(), SLOT(show()));
}

MainWindow::~MainWindow()
{
    delete stepperController;
    delete dcMotorController;
    delete ui;
}

