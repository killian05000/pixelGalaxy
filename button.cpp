#include "button.h"
#include <QDebug>

Button::Button()
    :QGraphicsRectItem()
{


}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *evt)
{
    emit clicked();
}
