#include "errorpopup.h"
#include "ui_errorpopup.h"

errorPopUp::errorPopUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::errorPopUp)
{
    ui->setupUi(this);

    QPalette palette = ui->label->palette();
    palette.setColor(ui->label->foregroundRole(), Qt::red);
    ui->label->setPalette(palette);

    //For background
    QString path = QFileInfo(".").absolutePath();
    path.append("/FirmwareUpdater/images/backgroundImage.jpg");
    QPixmap bkgnd(path);
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette bkgndPalette;
    bkgndPalette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(bkgndPalette);
}

errorPopUp::~errorPopUp()
{
    delete ui;
}

void errorPopUp::changeText(QString txt){
    ui->label->setText(txt);
}

void errorPopUp::on_OKButton_clicked()
{
    close();
}

