#ifndef ERRORPOPUP_H
#define ERRORPOPUP_H

#include <QDialog>
#include <QFileDialog>
#include <QDebug>

namespace Ui {
class errorPopUp;
}

class errorPopUp : public QDialog
{
    Q_OBJECT

public:
    explicit errorPopUp(QWidget *parent = nullptr);
    ~errorPopUp();

    void changeText(QString txt);

private slots:
    void on_OKButton_clicked();

private:
    Ui::errorPopUp *ui;
};

#endif // ERRORPOPUP_H
