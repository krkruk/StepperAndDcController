#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QMessageBox>
#include <QTimer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class SerialPort : public QObject
{
    Q_OBJECT
    static constexpr int TIMER_INTERVAL_MS {200};
    void connects();
public:
    explicit SerialPort(QObject *parent = 0);
    ~SerialPort();
    void setPortName(const QString &name);
    bool open();
    void close();
    bool isOpen() const;
    void setSerialMsgToSend(const QJsonObject &msg);

signals:
    void readLine(const QString &line);
    void connectionClosed();

public slots:

private slots:
    void lineReceived();
    void serialError(QSerialPort::SerialPortError e);
    void onTimerTimeout();

private:
    QSerialPort *serial;
    QTimer *timer;
    QJsonObject jsonToSend;
};

#endif // SERIALPORT_H
