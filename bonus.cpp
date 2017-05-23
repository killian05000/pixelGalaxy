#include "bonus.h"
#include "enemytype1.h"
#include "bullet.h"
#include "game.h"
#include "player.h"

#include <QGraphicsScene>
#include <QDebug>
#include <typeinfo>
#include <QList>

extern Game *game;

random_device Bonus::generator{};

Bonus::Bonus()
     : QObject(), QGraphicsPixmapItem()
{}

Bonus::~Bonus()
{}

void Bonus::heartSpawn()
{
    uniform_int_distribution<int> distribution(0,750);
    int random_number = distribution(generator);
    setPos(random_number, -50);

    QTimer *heartMoveTimer;
    heartMoveTimer = new QTimer();
    heartMoveTimer->start(30);

    connect(heartMoveTimer, &QTimer::timeout, this, &Bonus::moveHeartBonus);
}

void Bonus::moveHeartBonus()
{
    if (game->playerShip->getIsRunning() == true)
        setPos(x(),y()+5);


    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i=0, n = colliding_items.size(); i < n; i++)
    {
        if (typeid(*(colliding_items[i])) == typeid(Player))
        {
            //scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            //delete colliding_items[i];
            delete this;
            qDebug() << "Life item colision to " << pos().y();
            game->playerLife->increaseLife();
            return;
        }
    }

    if (game->playerShip->gameReset==true)
        delete this;
}

void Bonus::tripleBulletSpawn()
{
    uniform_int_distribution<int> distribution(0,750);
    int random_number = distribution(generator);
    setPos(random_number, -50);

    QTimer *tripleBulletMoveTimer;
    tripleBulletMoveTimer = new QTimer();
    tripleBulletMoveTimer->start(30);

    connect(tripleBulletMoveTimer, &QTimer::timeout, this, &Bonus::moveTripleBulletBonus);
}

void Bonus::moveTripleBulletBonus()
{
    if (game->playerShip->getIsRunning() == true)
        setPos(x(),y()+5);


    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i=0, n = colliding_items.size(); i < n; i++)
    {
        if (typeid(*(colliding_items[i])) == typeid(Player))
        {
            //scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            //delete colliding_items[i];
            delete this;
            qDebug() << "tripleBulletBonus item colision to " << pos().y();
            game->playerShip->tripleBulletBonusActivated=true;
            return;
        }
    }

    if (game->playerShip->gameReset==true)
        delete this;
}

void Bonus::specialBulletSpawn()
{
    uniform_int_distribution<int> distribution(0,750);
    int random_number = distribution(generator);
    setPos(random_number, 0);

    QTimer *specialBulletMoveTimer;
    specialBulletMoveTimer = new QTimer();
    specialBulletMoveTimer->start(30);

    connect(specialBulletMoveTimer, &QTimer::timeout, this, &Bonus::moveSpecialBulletBonus);
}

void Bonus::moveSpecialBulletBonus()
{
    if (game->playerShip->getIsRunning() == true)
        setPos(x(),y()+5);


    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i=0, n = colliding_items.size(); i < n; i++)
    {
        if (typeid(*(colliding_items[i])) == typeid(Player))
        {
            //scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            //delete colliding_items[i];
            delete this;
            qDebug() << "specialBulletBonus item colision to " << pos().y();
            game->playerShip->specialBulletBonusActivated=true;
            return;
        }
    }

    if (game->playerShip->gameReset==true)
        delete this;
}
