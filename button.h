#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QMouseEvent>

class Button : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Button();

protected:
    //void mousePressEvent(QGraphicsSceneMouseEvent *evt);
    //QMouseEvent *bidule;

signals:
    void clicked();
};

#endif // BUTTON_H
