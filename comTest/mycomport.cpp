#include "mycomport.h"



MyComPort::MyComPort()
{
    this->serial = new QSerialPort();

    QObject::connect(this->serial, &QSerialPort::readyRead,this, &MyComPort::readData);

    QObject::connect(this->serial,
                     static_cast<void(QSerialPort::*)(QSerialPort::SerialPortError)>
                     (&QSerialPort::error),
                     [&](QSerialPort::SerialPortError error)
    {
        //this is called when a serial communication error occurs
        qDebug() << "An error occured: " << error;
    });


    openSerialPort();
}

void MyComPort::openSerialPort()
{
    this->serial->setPortName("COM12");
    this->serial->setBaudRate(QSerialPort::Baud115200);
    this->serial->setDataBits(QSerialPort::Data8);
    this->serial->setParity(QSerialPort::NoParity);
    this->serial->setStopBits(QSerialPort::OneStop);
    this->serial->setFlowControl(QSerialPort::HardwareControl);

    if (this->serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "Success" ;
    }
    else
    {
        std::cout << "Error with comport" << std::endl;
    }

     QTimer::singleShot(2000, this, SLOT(temp()));

}

void MyComPort::temp(){
    qDebug() << "rfsdfgfdhgfjhgf";
    QString str("scan start\r");
    QByteArray br = str.toUtf8();
    this->writeData(br);
}

void MyComPort::writeData(const QByteArray &data)
{
    const char *a = "scan start \n\r";
    this->serial->write(a);
}

void MyComPort::readData(){
    //this is called when readyRead() is emitted
    //qDebug() << "New data available: " << serial.bytesAvailable();
    QByteArray datas =serial->readAll();
    qDebug() << datas;

}
