#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <maincomportwindow.h>
#include <QTimer>
#include <QSerialPortInfo>
#include <QComboBox>
#include <QApplication>
#include "serialport.h"
#include <QObject>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QtGlobal>
#include <QPalette>

#include <popup.h>
#include <styling.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString getComPort();
    QString getFilePath();

private slots:
    void on_startButton_clicked();
    void changeWindow();

    void on_SelectFileButton_clicked();

    void setComPort(QString COM);

private:
    Ui::MainWindow *ui;
    popUp* popup;
    QTimer * timer;
    Styling* style;
    SerialPort serialport;
    QString COMport;
    QString filePath;
};
#endif // MAINWINDOW_H
