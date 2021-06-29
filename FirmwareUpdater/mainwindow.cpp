#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
    The first windows shown to the user after starting the application
*/


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Initializing
    popup = new popUp();
    style = new Styling();

    //Used styling buttons
    style->changeButton( ui->startButton);

    timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&MainWindow::changeWindow);

    //Detects which COM-ports are open
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        ui->comboBox->addItem(serialPortInfo.portName());
        ui->comboBox->setCurrentIndex(1);
    }

    //Coloring error text
    QPalette palette = ui->errorLbl->palette();
    palette.setColor(ui->errorLbl->foregroundRole(), Qt::red);
    ui->errorLbl->setPalette(palette);

    //For background
    QString path = QFileInfo(".").absolutePath();
    path.append("/FirmwareUpdater/images/backgroundImage.jpg");
    QPixmap bkgnd(path);
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette bkgndPalette;
    bkgndPalette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(bkgndPalette);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeWindow(){

    if(popup->isVisible()){
        popup->hide();
        this->show();
    }else{
        this->hide();
        popup->show();
    }
}

void MainWindow::on_startButton_clicked()
{
        if(filePath.isEmpty()){
            qWarning("You did not choose a file");
            ui->errorLbl->setText("You did not choose any file");
        }else if (!filePath.contains(".img")) {
            qWarning("You have chosen a wrong file");
            ui->errorLbl->setText("You did not choose an '.img' file. Please try again");
        }else if(ui->comboBox->currentText().isEmpty()){
            qWarning("no device found");
            ui->errorLbl->setText("No device has been selected");
        }else{
            popup->setComport(ui->comboBox->currentText());
            popup->setFilePath(filePath);
            popup->show();
            qDebug() << getComPort();
        }
}

void MainWindow::on_SelectFileButton_clicked()
{
    filePath=QFileDialog::getOpenFileName(this, "Find your .img file");
}

QString MainWindow::getFilePath(){
    return filePath;
}

void MainWindow::setComPort(QString COM){
    COMport = COM;
}

QString MainWindow::getComPort(){
    return COMport;
}


