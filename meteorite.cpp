#include "meteorite.h"
#include "game.h"

#include <QGraphicsScene>
#include <QDebug>
#include <typeinfo>
#include <QList>
#include <QTimer>
#include <random>

extern Game * game;

random_device Meteorite::generator{};

Meteorite::Meteorite()
         : QObject(), QGraphicsPixmapItem()
{}

void Meteorite::meteoriteSpawn()
{
    uniform_int_distribution<int> distribution(0,700);
    int random_number = distribution(generator);
    setPos(random_number, -pixmap().height()); //Faire 3 skins de meteorite de taille différente dans game.cpp

    QTimer *meteoriteMoveTimer = new QTimer;
    meteoriteMoveTimer->start(25);

    connect(meteoriteMoveTimer, &QTimer::timeout, this, &Meteorite::move);
}

void Meteorite::move()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
     for (int i=0, n = colliding_items.size(); i < n; i++)
     {
         if (typeid(*(colliding_items[i])) == typeid(Player))
         {
             game->playerLife->decreaseLife();
             if (game->playerLife->getLife() == 0)
             {
                 game->playerGameOver->paintGameOver();
                 scene()->addItem(game->playerGameOver);
                 game->playerShip->setIsRunning(false);
             }
             scene()->removeItem(this);
             delete this;
             qDebug() << "Meteorite item colision to " << pos().y();
             return;
         }
     }

    if (game->playerShip->getIsRunning()==true)
        setPos(x(),y()+5);

    if ((game->playerLife->getLife() <= 0) && (game->playerShip->getIsRunning() == true))
    {
        game->playerGameOver->paintGameOver();
        scene()->addItem(game->playerGameOver);
        qDebug() << "On paralyse l'écran";
        game->playerShip->setIsRunning(false);
        return;
    }

    if (pos().y() - pixmap().height() >= 600)
   {
       scene()->removeItem(this);
       delete this;
       qDebug() << "meteorite deleted to " << pos().y();
    }
}
