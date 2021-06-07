#include "serialport.h"

SerialPort::SerialPort()
{
    serial = new QSerialPort(this);
    connect(serial, SIGNAL(readyRead()), this, SLOT(ReadData()));
}

SerialPort::~SerialPort(){

}

//This function opens the connection with the serial port and sets the right
// properties
void SerialPort::openSerialPort(QString com){
    serial->setPortName(com);
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::HardwareControl);
    if(serial->open(QIODevice::ReadWrite) && serial->isOpen()){
        showStatusMessage("Connected!");
        serial->setDataTerminalReady(1);

    }else{
        showStatusMessage(tr("Error while opening"));
    }
}

//If a serial communication is present, this function
// closes it
void SerialPort::closeSerialPort(){
    if(serial->isOpen()){
        serial->close();
        showStatusMessage(tr("Disconnected"));
    }else{

        showStatusMessage("Nothing open to close");
    }
}

void SerialPort::WriteData(QString message){
    if(this->serial->bytesAvailable() <= 0){
        std::string messageToSend = message.toStdString();
        messageToSend = "\r\n " + messageToSend + " \r\n";
        const char *data = messageToSend.c_str();
        this->serial->write(data);
    }
}

void SerialPort::ReadData(){
    //this is called when readyRead() is emitted
    //qDebug() << "New data available: " << serial.bytesAvailable();

    this->datas += serial->readAll();
    qDebug() << this->datas;
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

//Scans for bluetooth devices in the area
void SerialPort::Scan(){
    QByteArray data = "scan start";
    qDebug() << data;
    this->WriteData(data);
}

//Updates bluetooth device
void SerialPort::Update(){
    QByteArray data = "update gatt";
    qDebug() << data;
    this->WriteData(data);
}

//STILL HAS SO NUMBER HAS TO BE SELECTED
void SerialPort::ConnectDevice(QString version){
    QString data = "connect ";
    data.append(version);
    qDebug() << data;
    this->WriteData(data);
}

void SerialPort::ProcessData(QByteArray data){

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

//HandleError which makes sure errors are coverd
// the serial port is closed when this error exists
void SerialPort::handleError(QSerialPort::SerialPortError error){
    if(error == QSerialPort::NoError){
        qDebug() << "Port open!";
    } else if(error == QSerialPort::ResourceError){
        closeSerialPort();
    } else{
        qDebug() << "An error occured: " << error;
    }
}

// This function shows any message using qDebug and prints it
// on the console
void SerialPort::showStatusMessage(const QString &message){
    qDebug() << message;
}
