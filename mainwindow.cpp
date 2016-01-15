#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stepperSettingsDialog = new StepperSettingsDialog(this);
    stepper1 = new StepperControlWidget(this);
    dc1 = new DCMotorControlWidget(this);

    ui->tabWidgetStepperSelect->addTab(stepper1, "Stepper1");
    ui->tabWidgetDCMotorSelect->addTab(dc1, "Motor 1");

    connect(ui->actionStepper, SIGNAL(triggered(bool)), stepperSettingsDialog, SLOT(show()));
}

MainWindow::~MainWindow()
{
    delete dc1;
    delete stepper1;
    delete stepperSettingsDialog;
    delete ui;
}

