#include "popup.h"
#include "ui_popup.h"

popUp::popUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::popUp)
{
    ui->setupUi(this);

    errorpopup = new errorPopUp();
    mainComportWindow = new MainComportWindow();
    timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&popUp::changeWindow);

    //For background
    QString path = QFileInfo(".").absolutePath();
    path.append("/FirmwareUpdater/images/backgroundImage.jpg");
    QPixmap bkgnd(path);
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette bkgndPalette;
    bkgndPalette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(bkgndPalette);
}

popUp::~popUp()
{
    delete ui;
}

void popUp::setComport(QString comm){
    COMM = comm;
}

void popUp::setFilePath(QString fp){
    FilePath = fp;
}

void popUp::cliProgrammer(){

    QProcess CommandPrompt;
    QStringList Arguments;
    QString path = QFileInfo(".").absolutePath();
    path.append("/FirmwareUpdater/programmer/cli_programmer.exe");
    qDebug() << path;

    Arguments << this->COMM << "write_qspi" << "0x300000" << this->FilePath;
//    CommandPrompt.start("C:\\Users\\hossa\\OneDrive\\Documenten\\QTprograms\\FirmwareUpdater\\programmer\\cli_programmer.exe",Arguments);
    CommandPrompt.start(path ,Arguments);

    bool val = CommandPrompt.waitForFinished();
    /*while(!CommandPrompt.atEnd()){
        qDebug() << CommandPrompt.readAllStandardOutput();
    }*/
    qDebug() << val;
    QByteArray text = CommandPrompt.readAllStandardOutput();
    qDebug() << text.contains("done.");
    qDebug() << text;

    if(text.contains("done.")){
        errorpopup->changeText("Reset device one last time");
        mainComportWindow->show();
        mainComportWindow->setSelection(this->COMM);
        errorpopup->show();
    }else{
        errorpopup->show();
    }
}

void popUp::changeWindow(){
    if(errorpopup->isVisible()){
        errorpopup->hide();
        this->show();
    }else{
        this->hide();
        errorpopup->show();
    }

    if(mainComportWindow->isVisible()){
        mainComportWindow->hide();
        this->show();
    }else{
        this->hide();
        mainComportWindow->show();
    }
}

void popUp::on_OKButton_clicked()
{
    cliProgrammer();
}

