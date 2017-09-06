#include "bosstype1.h"
#include "enemytype1.h"
#include "bullet.h"
#include "game.h"
#include "player.h"

#include <QGraphicsScene>
#include <QDebug>
#include <typeinfo>
#include <QList>
#include <QTimer>

extern Game *game;

random_device BossType1::generator{};

BossType1::BossType1()
         :QObject(), QGraphicsPixmapItem()
{
    bossLife=60;
}

BossType1::~BossType1()
{}

void BossType1::bossType1Spawn()
{
    setPos((400-pixmap().width()/2), -pixmap().height());

    QTimer *BossType1MoveTimer = new QTimer;
    BossType1MoveTimer->start(50);

    QTimer *shotFirstBulletTimer = new QTimer();
    shotFirstBulletTimer->start(1200);

    QTimer *shotSecondBulletTimer = new QTimer();
    shotSecondBulletTimer->start(1000);

    QTimer *shotThirdBulletTimer = new QTimer();
    shotThirdBulletTimer->start(1000);

    if (game->playerLife->getLife() <= 0)
    {
        shotFirstBulletTimer->setSingleShot(1);
        shotSecondBulletTimer->setSingleShot(2);
        shotThirdBulletTimer->setSingleShot(3);
    }

    connect(BossType1MoveTimer, &QTimer::timeout, this, &BossType1::move);
    connect(shotFirstBulletTimer, &QTimer::timeout, this, &BossType1::shotFirstBullet);
    connect(shotSecondBulletTimer, &QTimer::timeout, this, &BossType1::shotSecondBullet);
    connect(shotThirdBulletTimer, &QTimer::timeout, this, &BossType1::shotThirdBullet);
}

void BossType1::move()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
     for (int i=0, n = colliding_items.size(); i < n; i++)
     {
         if (typeid(*(colliding_items[i])) == typeid(Player))
         {
             game->playerLife->setLife(0);
             game->playerGameOver->paintGameOver();
             scene()->addItem(game->playerGameOver);
             game->playerShip->setIsRunning(false);
             scene()->removeItem(this);
             delete this;
             qDebug() << "Boss item colision to " << pos().y();
             return;
         }
     }

     if (pos().y() >= 800)
    {
         game->playerLife->setLife(0);
         game->playerShip->setIsRunning(false);
         scene()->removeItem(this);
         delete this;
         game->playerScore->bossType1Activated=false;
         qDebug() << "Boss deleted by crossing the line to " << pos().y();
         game->playerGameOver->paintGameOver();
         scene()->addItem(game->playerGameOver);
         return;
     }

    if (game->playerShip->getIsRunning()==true)
    {
        uniform_int_distribution<int> distribution(1,400);
        int random_number = distribution(generator);

        int moveL;
        int moveR;

        if (pos().x() <= 100)
        {
            qDebug() <<" trop à gauche 100 crossed";
            moveL=1;
            moveR=3;
        }
        else if (pos().x() >= 300)
        {
            qDebug() << "trop à droite 500 crossed";
            moveL=3;
            moveR=1;
        }
        else
        {
            moveL=3;
            moveR=3;
        }

        if ((random_number <= 150) && (pos().x() >= 5))
            setPos(x()-moveL,y());
        else if ((random_number <= 300) && (pos().x() <= 795))
            setPos(x()+moveR,y());
        else if (random_number > 300)
            setPos(x(),y()+2);


//        if (pos().y() <=0)
//            setPos(x(), y()+2);
//        else if ((pos().y() < 100) && (pos().x() <= 200) && (pos().y() >0))
//            setPos(x()-1, y()+2);
//        else if ((pos().y() >= 100) && (pos().y() < 200) && (pos().x() < 200))
//            setPos(x()+1, y()+2);
//        else if ((pos().y() <= 200) && (pos().x() >= 200) && (pos().y() >= 100))
//            setPos(x()+1, y()-2);
//        else if ((pos().y() < 100) && (pos().x() > 200) && (pos().y() >0))
//            setPos(x()-1, y()-2);

    }

    if ((game->playerLife->getLife() <= 0) && (game->playerShip->getIsRunning() == true))
    {
        game->playerGameOver->paintGameOver();
        scene()->addItem(game->playerGameOver);
        qDebug() << "On paralyse l'écran";
        game->playerShip->setIsRunning(false);
        return;
    }

    if (game->playerShip->gameReset==true)
        delete this;
}

void BossType1::shotFirstBullet()
{
    if ((game->playerLife->getLife() > 0) && (game->playerShip->getIsRunning()==true))
    {
        Bullet *firstBossBullet = new Bullet();
        firstBossBullet->setPixmap(QPixmap(":/pictures/Images/redLazerBullet.png"));
        firstBossBullet->setPos((x()+pixmap().width()/2) , y()+pixmap().height());
        scene()->addItem(firstBossBullet);

        QTimer *firstBossBulletSpeed = new QTimer();
        firstBossBulletSpeed->start(20);

        connect(firstBossBulletSpeed, &QTimer::timeout, firstBossBullet, &Bullet::bossFirstBulletMove);
    }
}

void BossType1::shotSecondBullet()
{
    if ((game->playerLife->getLife() > 0) && (game->playerShip->getIsRunning()==true))
    {
        Bullet *secondBossBullet = new Bullet();
        secondBossBullet->setPixmap(QPixmap(":/pictures/Images/redLazerBullet.png"));
        secondBossBullet->setPos((x()+pixmap().width()*0.2) , y()+pixmap().height());
        scene()->addItem(secondBossBullet);

        QTimer *secondBossBulletSpeed = new QTimer();
        secondBossBulletSpeed->start(20);

        connect(secondBossBulletSpeed, &QTimer::timeout, secondBossBullet, &Bullet::bossSecondBulletMove);
    }
}

void BossType1::shotThirdBullet()
{
    if ((game->playerLife->getLife() > 0) && (game->playerShip->getIsRunning()==true))
    {
        Bullet *thirdBossBullet = new Bullet();
        thirdBossBullet->setPixmap(QPixmap(":/pictures/Images/redLazerBullet.png"));
        thirdBossBullet->setPos((x()+pixmap().width()*0.8) , y()+pixmap().height());
        scene()->addItem(thirdBossBullet);

        QTimer *thirdBossBulletSpeed = new QTimer();
        thirdBossBulletSpeed->start(20);

        connect(thirdBossBulletSpeed, &QTimer::timeout, thirdBossBullet, &Bullet::bossThirdBulletMove);
    }
}

void BossType1::decreaseBossLife()
{
    bossLife--;
}

int BossType1::getBossLife()
{
    return bossLife;
}
