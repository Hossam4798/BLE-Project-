#ifndef SERIALPORT_H
#define SERIALPORT_H
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QSerialPort>
#include <QtSerialPort/QtSerialPort>
#include <QObject>
#include <QMessageBox>
#ifdef Q_OS_WIN
#include <windows.h> // for Sleep
#endif

class SerialPort : public QSerialPort{

    Q_OBJECT
public:
    SerialPort();
    virtual ~SerialPort();

    QList<QPair<QString,QPair<QString,QString>>> numberAndAddress;

public slots:
    void openSerialPort(QString com);
    void closeSerialPort();

    void Scan();
    void Update();
    void ConnectDevice(QString version);

    void WriteData(QString message);
    void ReadData();

    void ProcessData(QByteArray data);
    void handleError(QSerialPort::SerialPortError error);

private:
    void showStatusMessage(const QString &message);

    QSerialPort *serial;
    QByteArray datas;    // The data buffer
};

#endif // SERIALPORT_H
