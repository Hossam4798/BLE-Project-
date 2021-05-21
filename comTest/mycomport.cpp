#include "mycomport.h"
#include <string>
#include <QProcess>
#include <QString>
#include <QPair>
#include <qpair.h>
MyComPort::MyComPort(QString portName)
{
    this->serial = new QSerialPort();
    this->portName = portName;
    QObject::connect(this->serial, &QSerialPort::readyRead,this, &MyComPort::ReadData);

    QObject::connect(this->serial,
                     static_cast<void(QSerialPort::*)(QSerialPort::SerialPortError)>
                     (&QSerialPort::error), this, &MyComPort::PortError);


    OpenSerialPort();
}

MyComPort::~MyComPort(){

    if(this->serial != nullptr){
        delete this->serial;
    }

}

void MyComPort::OpenSerialPort()
{
    this->serial->setPortName(this->portName);
    this->serial->setBaudRate(QSerialPort::Baud115200);
    this->serial->setDataBits(QSerialPort::Data8);
    this->serial->setParity(QSerialPort::NoParity);
    this->serial->setStopBits(QSerialPort::OneStop);
    this->serial->setFlowControl(QSerialPort::HardwareControl);

    if (this->serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "ReadWrite ready!" ;
    }
    else
    {
        qDebug() << "Error with comport";
    }

    QTimer::singleShot(6000, this, SLOT(temp()));

}

void MyComPort::temp(){

    //const char *a = "\r\n scan start \r\n";
    QString mes = "scan start";
    this->WriteData(mes);
}

void MyComPort::WriteData(QString message)
{
    if(this->serial->bytesAvailable() <= 0){
        std::string messageToSend = message.toStdString();
        messageToSend = "\r\n " + messageToSend + " \r\n";
        const char *data = messageToSend.c_str();
        this->serial->write(data);
    }
}

void MyComPort::ReadData(){
    //this is called when readyRead() is emitted
    //qDebug() << "New data available: " << serial.bytesAvailable();

    this->datas += serial->readAll();

    if(this->datas.back() == '\n'){

        qDebug() << this->datas;
        qDebug() << "check";
        this->ProcessData(this->datas);
        this->datas.clear();
    }


}

void MyComPort::PortError(QSerialPort::SerialPortError error){

    //this is called when a serial communication error occurs
    if(error == QSerialPort::NoError){
        qDebug() << "Port open!";
    } else{
        qDebug() << "An error occured: " << error;
    }

}

void MyComPort::ProcessData(QByteArray data){

    QString q_data = QString(data);
    QRegExp regexp(" public ");

    QPair<QString,QString> tempNumAndAdd;

    QString address = "";
    int i = 0;
    int firstBracket = 0;
    int copyNumber = 8; // The word "public" with 2 whitespaces is 8 long

    if(q_data.contains('[',Qt::CaseSensitive) == true){


        firstBracket = q_data.indexOf("[");
        // Check if the fourth character is a ']'

        if(q_data[firstBracket+3] == "]"){
            tempNumAndAdd.first = q_data.mid(firstBracket+1,2);
            i = q_data.indexOf(regexp);
            qDebug() << "Found!!!!!";
            if(i != -1){
                // Get the address
                while(i+copyNumber < q_data.length()){

                    if(q_data[i+copyNumber] == " " || q_data[i+copyNumber] == "\r"){
                        break;

                    }
                    address.append(q_data[i+copyNumber]);
                    copyNumber++;
                }
                tempNumAndAdd.second = address;
            }
            this->numberAndAddress.append(tempNumAndAdd);
             qDebug() << this->numberAndAddress.first().first;
             qDebug() << this->numberAndAddress.first().second;
        }
    }

}


