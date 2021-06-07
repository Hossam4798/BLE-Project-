#include "maincomportwindow.h"
#include "ui_maincomportwindow.h"
#include "mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QPixmap>
#include <QDebug>
#include <QFileDialog>

#ifdef Q_OS_WIN
#include <windows.h> // for Sleep
#endif

MainComportWindow::MainComportWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainComportWindow)
{
    ui->setupUi(this);

    errorpopup = new errorPopUp();

    //Make an empty table
    ui->table->setRowCount(100);
    ui->table->setColumnCount(3);
    m_TableHeader<<"Firmware Version"<<"Number"<<"Device address";
    ui->table->setHorizontalHeaderLabels(m_TableHeader);

    //For background
    QString path = QFileInfo(".").absolutePath();
    path.append("/FirmwareUpdater/images/backgroundImage.jpg");
    QPixmap bkgnd(path);
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette bkgndPalette;
    bkgndPalette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(bkgndPalette);
}

//Destructor which stops the commisioning and closes the connection
// with the serial port
MainComportWindow::~MainComportWindow()
{
    serialport.closeSerialPort();
    delete ui;
}

//This function passes the COM-port to the serialPort
// function inside SerialPort.cpp
void MainComportWindow::setSelection(QString selection){
    serialport.openSerialPort(selection);
}

void MainComportWindow::setTable(){
    serialport.WriteData("scan stop");
    ui->table->clearContents();
    ui->table->setHorizontalHeaderLabels(m_TableHeader);
    ui->table->setSelectionMode(QAbstractItemView::SingleSelection);

    for(int column1 = 0; column1< ui->table->columnCount(); column1++){
        for(int row1 = 0; row1 < ui->table->rowCount(); row1++){
            ui->table->setItem(row1, column1, new QTableWidgetItem(""));
            ui->table->item(row1,column1)->setFlags(Qt::NoItemFlags);
        }
    }

    int row = 0;
    int column = 0;

    for(QPair<QString,QPair<QString,QString>> temp : this->serialport.numberAndAddress){
        ui->table->setItem(row, column, new QTableWidgetItem(temp.first));
        ui->table->setItem(row, column+1, new QTableWidgetItem(temp.second.first));
        ui->table->setItem(row, column+2, new QTableWidgetItem(temp.second.second));
        ui->table->item(row,0)->setFlags(Qt::NoItemFlags);
        ui->table->item(row,1)->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        ui->table->item(row,2)->setFlags(Qt::NoItemFlags);
        column = 0;
        row++;
    }

    qDebug() << "Size of data is " << this->serialport.numberAndAddress.length();
}

void MainComportWindow::on_ScanButton_clicked()
{
    serialport.Scan();
//    QTimer::singleShot(6000, this, SLOT(Scan));
}


void MainComportWindow::on_RefreshButton_clicked()
{
    setTable();
}

void MainComportWindow::on_ConnectButton_clicked()
{
    QList<QTableWidgetItem*> selectedItem  = ui->table->selectedItems();
    if(selectedItem.length() == 1 && selectedItem.first()->text().size() == 2){
        serialport.ConnectDevice(selectedItem.first()->text());
        qDebug() << selectedItem.first()->text().size();
    }else{
        errorpopup->changeText("None or more than threshhold selected!");
        errorpopup->show();
        qDebug() << "None or more than threshhold selected";
    }
}

void MainComportWindow::changeWindow(){
    if(errorpopup->isVisible()){
        errorpopup->hide();
        this->show();
    }else{
        this->hide();
        errorpopup->show();
    }
}


void MainComportWindow::on_UpdateButton_clicked()
{
    serialport.Update();
}

