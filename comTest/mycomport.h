#ifndef MYCOMPORT_H
#define MYCOMPORT_H

#include <QByteArray>
#include <QtSerialPort>
#include <iostream>
#include <QObject>

class MyComPort :public QObject
{
private:
    Q_OBJECT
public:

    MyComPort(QString portName);
    virtual ~MyComPort();

public:
    void OpenSerialPort();
    void WriteData(QString message);
    void ReadData();
    void PortError(QSerialPort::SerialPortError error);

private:
    void ProcessData(QByteArray data);

private slots:
    void temp();

private:
    QSerialPort* serial; // The serial port
    QString portName;    // The name of the serial port
    QByteArray datas;    // The data buffer
    QList<QPair<QString,QString>> numberAndAddress;
};

#endif // MYCOMPORT_H
