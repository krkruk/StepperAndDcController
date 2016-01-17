#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

void MainWindow::updateUartDevices()
{
    auto uartDevices = QSerialPortInfo::availablePorts();
    ui->comboBoxUartDeviceSelect->clear();
    for(const auto &portInfo : uartDevices)
        ui->comboBoxUartDeviceSelect->addItem(portInfo.portName());
}

void MainWindow::connects()
{
    connect(ui->actionStepper, SIGNAL(triggered(bool)), stepperSettingsDialog.get(), SLOT(show()));
    connect(serial, SIGNAL(connectionClosed()), this, SLOT(enableSerialWidgets()));
    connect(serial, SIGNAL(readLine(QByteArray)), this, SLOT(readSerialLine(QByteArray)));

    connect(dcMotorController, SIGNAL(dcMotorJsonUpdate(QJsonObject)),
            this, SLOT(setSerialMsgToSend(QJsonObject)));
    connect(stepperController, SIGNAL(stepperJsonUpdate(QJsonObject)),
                this, SLOT(setSerialMsgToSend(QJsonObject)));
}

void MainWindow::openSerialConnection()
{
    auto portName = ui->comboBoxUartDeviceSelect->currentText();
    if(!portName.isEmpty())
    {
        serial->setPortName(portName);
        if(serial->open())
        {
            disableSerialWidgets();
            setStatusBarMsg(5000, tr("Connection established..."));
        }
    }
}

void MainWindow::setStatusBarMsg(int time, const QString &str)
{
    ui->statusBar->showMessage(str, time);
}

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


    stepperController = new StepperWidgetController(
                ui->tabWidgetStepperSelect, this);
    stepperController->startInternalEnumerationAt(1);
    stepperController->addTab(Consts::STEPPER1_LABEL);
    stepperController->addTab(Consts::STEPPER2_LABEL);


    stepperSettingsDialog = stepperController->createSettingsDialog();

    serial = new SerialPort(this);

    connects();
    updateUartDevices();
}

MainWindow::~MainWindow()
{
    serial->close();
    delete serial;
    delete stepperController;
    delete dcMotorController;
    delete ui;
}

void MainWindow::enableSerialWidgets()
{
    setStatusBarMsg(5000, tr("Connection closed..."));
    dcMotorController->reset();
    stepperController->reset();
    dcMotorController->setSlidersEnabled(false);
    stepperController->setSlidersEnabled(false);
    ui->comboBoxUartDeviceSelect->setEnabled(true);
    ui->pushButtonUartReload->setEnabled(true);
    ui->pushButtonUartConnect->setText(tr("&Connect"));
}

void MainWindow::disableSerialWidgets()
{
    dcMotorController->setSlidersEnabled(true);
    stepperController->setSlidersEnabled(true);
    ui->comboBoxUartDeviceSelect->setEnabled(false);
    ui->pushButtonUartReload->setEnabled(false);
    ui->pushButtonUartConnect->setText(tr("Dis&connect"));
}

void MainWindow::setSerialMsgToSend(const QJsonObject &json)
{
    serial->setSerialMsgToSend(json);
}

void MainWindow::readSerialLine(const QByteArray &line)
{
    dcMotorController->dcMotorUpdateFeedback(line);
    stepperController->stepperUpdateFeedback(line);
}


void MainWindow::on_pushButtonUartReload_clicked()
{
    updateUartDevices();
}

void MainWindow::on_pushButtonUartConnect_clicked()
{
    if(!serial->isOpen())
        openSerialConnection();
    else
        serial->close();
}

void MainWindow::on_action_Exit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_action_Author_triggered()
{
    QString msg = "<p><h3>Stepper and DC Motor Controller</h3></p>"
                  "<p>Control stepper motors and dc motors via serial port.</p>"
                  "<p>&copy; <a href=\"mailto:krzysztof.pawel.kruk@gmail.com\">"
                  "Krzysztof Kruk</a> 2016</p>";
    QMessageBox::about(this, tr("About"), msg);
}

void MainWindow::on_action_About_Qt_triggered()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}
