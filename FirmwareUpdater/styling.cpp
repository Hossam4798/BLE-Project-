#include "styling.h"

Styling::Styling()
{

}

void Styling::changeButton(QPushButton* button){
    QPalette palette = button->palette();
    palette.setColor(QPalette::Button, QColor(Qt::blue));
    button->setAutoFillBackground(true);
    button->setPalette(palette);
    button->update();
    button->show();
}
