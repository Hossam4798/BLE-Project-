#ifndef POPUP_H
#define POPUP_H

#include <QDialog>
#include <QProcess>
#include <QDebug>
#include <QString>
#include <QTimer>
#include <QFileDialog>

#include <maincomportwindow.h>
#include <errorpopup.h>

namespace Ui {
class popUp;
}

class popUp : public QDialog
{
    Q_OBJECT

public:
    explicit popUp(QWidget *parent = nullptr);
    ~popUp();

public slots:
    void setComport(QString comm);
    void setFilePath(QString fp);
    void cliProgrammer();

private slots:
    void changeWindow();

    void on_OKButton_clicked();

private:
    Ui::popUp *ui;
    MainComportWindow* mainComportWindow;
    errorPopUp* errorpopup;
    QTimer * timer;
    QString COMM;
    QString FilePath;
};

#endif // POPUP_H
