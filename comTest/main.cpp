#include <QCoreApplication>
#include "mycomport.h"
#include <Windows.h>

#include <QtSerialPort>

int main(int argc, char* argv[]){
    QCoreApplication a(argc, argv);

    MyComPort *port = new MyComPort("COM12");
    //delete port;

    QProcess CommandPrompt;
    QStringList Arguments;

    //Arguments << "COM3" << "write_qspi" << "0x300000" << "C:\\SDK_10.0.10.118\\SDK_10.0.10.118\\projects\\dk_apps\\demos\\update_receiver\\DA1469x-00-Release_QSPI_SUOTA\\pxp_reporter.img";
    //CommandPrompt.startDetached("C:\\SDK_10.0.10.118\\SDK_10.0.10.118\\binaries\\cli_programmer.exe",Arguments);

    return a.exec();
    //     ^^^^^^^^
    //very important: starts the Qt main event loop
    //this makes all asynchronous stuff possible
}

//cli_programmer.exe COM10 write_qspi 0x300000 C:\\SDK_10.0.10.118\\SDK_10.0.10.118\\projects\\dk_apps\\demos\\update_receiver\\DA1469x-00-Release_QSPI_SUOTA\\pxp_reporter.img
