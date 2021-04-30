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

    MyComPort();
    void openSerialPort();
    void writeData(const QByteArray &data);
    void readData();
    private slots:
    void temp();
public:
    QSerialPort* serial;
};

#endif // MYCOMPORT_H
