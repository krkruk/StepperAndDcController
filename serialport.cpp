#include "serialport.h"
#include <QWidget>
#include <QDebug>

void SerialPort::connects()
{
    connect(serial, SIGNAL(readyRead()), this, SLOT(lineReceived()));
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)),
            this, SLOT(serialError(QSerialPort::SerialPortError)));

    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerTimeout()));
}

SerialPort::SerialPort(QObject *parent)
    : QObject(parent)
{
    serial = new QSerialPort(this);
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    timer = new QTimer(this);
    timer->setInterval(TIMER_INTERVAL_MS);

    connects();
}

SerialPort::~SerialPort()
{
    close();
    delete serial;
}

void SerialPort::setPortName(const QString &name)
{
    if(!serial->isOpen())
        serial->setPortName(name);
}

bool SerialPort::open()
{
    if(!serial->isOpen())
    {
        if(serial->open(QSerialPort::ReadWrite))
        {
            timer->start();
            return true;
        }
    }
    return false;
}

void SerialPort::close()
{
    if(serial->isOpen())
    {
        timer->stop();
        serial->close();
        emit connectionClosed();
    }
}

bool SerialPort::isOpen() const
{
    return serial->isOpen();
}

void SerialPort::setSerialMsgToSend(const QJsonObject &msg)
{
    jsonToSend = msg;
}

void SerialPort::lineReceived()
{
    if(serial->canReadLine())
    {
        auto line = serial->readLine();
        line.remove(0,1);
        emit readLine(line);
    }
}

void SerialPort::serialError(QSerialPort::SerialPortError e)
{
    if(e != QSerialPort::NoError)
    {
        QMessageBox::critical(qobject_cast<QWidget *> (parent()), tr("Serial Error"), serial->errorString());
        close();
    }
}

void SerialPort::onTimerTimeout()
{
    if(serial->isOpen())
    {
        auto jsonDocument = QJsonDocument(jsonToSend);
        auto jsonData = jsonDocument.toJson(QJsonDocument::Compact);
        serial->write(jsonData + "\r\n");
        jsonToSend = QJsonObject();
    }
}
