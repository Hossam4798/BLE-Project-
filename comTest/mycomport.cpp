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

//    QTimer::singleShot(6000, this, SLOT(temp()));

}

//void MyComPort::temp(){

//    //const char *a = "\r\n scan start \r\n";
//    QString mes = "scan start";
//    this->WriteData(mes);
//}

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
    qDebug() << "In readData!!!!";
    if(this->datas.contains('\n')){
        while(this->datas.contains('\n')){

            qDebug() << "check";

            int num = this->datas.indexOf('\n');
            QByteArray sentence = this->datas.mid(0,num);
            this->ProcessData(sentence);

            qDebug() <<sentence;
            this->datas = this->datas.mid(num+1,this->datas.length()-num);
            qDebug() << this->datas;
        }
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
    QPair<QString, QPair<QString,QString>> device;
    bool deviceExists = false;
    QString address = "";
    int i = 0;
    int deviceCounter = 0;
    int firstBracket = 0;
    int copyNumber = 8; // The word "public" with 2 whitespaces is 8 long

    if(q_data.contains('[',Qt::CaseSensitive) == true){


        firstBracket = q_data.indexOf("[");
        // Check if the fourth character is a ']'

        if(q_data[firstBracket+3] == "]"){
            tempNumAndAdd.first = q_data.mid(firstBracket+1,2);

            QPair<QString, QPair<QString,QString>> checkName;
            foreach (checkName, this->numberAndAddress){
                if(QString::compare(tempNumAndAdd.first, checkName.second.first) == 0){
                    deviceExists = true;
                    break;
                }
                deviceCounter++;
            }



            if(!deviceExists){
                deviceCounter = 0; // reset device counter because no device was found

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
                device.second = tempNumAndAdd;
                this->numberAndAddress.append(device);
            }
            else{ // adding the firmware number
                    int firmWareStartPos = q_data.indexOf("(");
                    int firmWareEndPos = q_data.indexOf(")");
                    this->numberAndAddress[deviceCounter].first = q_data.mid(firmWareStartPos+1,firmWareEndPos - firmWareStartPos-1);
                     qDebug() << "Showing device!!!!!!!!!!!!!!!!!!!!!!!!!!!";
                    qDebug() << this->numberAndAddress[deviceCounter].first;
                    qDebug() << this->numberAndAddress[deviceCounter].second.first;
                    qDebug() << this->numberAndAddress[deviceCounter].second.second;
            }


        }
    }

}


