#ifndef MAINCOMPORTAPP_H
#define MAINCOMPORTAPP_H

#include "serialport.h"
#include <QMainWindow>
#include <errorpopup.h>
#include <QFileDialog>
#include <QDebug>

namespace Ui {
class MainComportWindow;
}

class MainComportWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainComportWindow(QWidget *parent = nullptr);
    ~MainComportWindow();

    void setSelection(QString selection);
    void setTable();

private slots:
    void changeWindow();

    void on_ScanButton_clicked();

    void on_RefreshButton_clicked();

    void on_ConnectButton_clicked();

    void on_UpdateButton_clicked();

private:
    Ui::MainComportWindow *ui;
    errorPopUp* errorpopup;
    SerialPort serialport;
    char list [300][20];
    QStringList m_TableHeader;
};

#endif // MAINCOMPORTWINDOW_H
