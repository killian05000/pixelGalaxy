#include "button.h"
#include <QDebug>

Button::Button()
    :QGraphicsRectItem()
{


}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *evt)
{
    qDebug() << Q_FUNC_INFO;
    emit clicked();
}
