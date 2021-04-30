#include <QCoreApplication>
#include "mycomport.h"
#include <Windows.h>

#include <QtSerialPort>

int main(int argc, char* argv[]){
    QCoreApplication a(argc, argv);
    //QSerialPort serial;
    MyComPort port;

    /*serial.setPortName("COM12");
    if(!serial.setBaudRate(QSerialPort::Baud115200))
        qDebug() << serial.errorString();
    if(!serial.setDataBits(QSerialPort::Data8))
        qDebug() << serial.errorString();
    if(!serial.setParity(QSerialPort::NoParity))
        qDebug() << serial.errorString();
    if(!serial.setFlowControl(QSerialPort::HardwareControl))
        qDebug() << serial.errorString();
    if(!serial.setStopBits(QSerialPort::OneStop))
        qDebug() << serial.errorString();
    if(!serial.open(QIODevice::ReadOnly))
        qDebug() << serial.errorString();
    QObject::connect(&serial, &QSerialPort::readyRead, [&]
    {
        //this is called when readyRead() is emitted
        //qDebug() << "New data available: " << serial.bytesAvailable();
        QByteArray datas = serial.readAll();
        qDebug() << datas;
    });
    QObject::connect(&serial,
                     static_cast<void(QSerialPort::*)(QSerialPort::SerialPortError)>
                     (&QSerialPort::error),
                     [&](QSerialPort::SerialPortError error)
    {
        //this is called when a serial communication error occurs
        qDebug() << "An error occured: " << error;
        a.quit();
    });*/





    return a.exec();
    //     ^^^^^^^^
    //very important: starts the Qt main event loop
    //this makes all asynchronous stuff possible
}
