#include "bullet.h"
#include "game.h"
#include "player.h"
#include "enemytype1.h"
#include "enemytype2.h"
#include "enemytype3.h"
#include "score.h"
#include "bosstype1.h"
#include "meteorite.h"
#include "bonus.h"

#include <QDebug>
#include <QList>
#include <typeinfo>

extern Game *game;

random_device Bullet::generator{};

Bullet::Bullet()
{
//    exploSound = new QMediaPlayer;
//    exploSound->setMedia(QUrl("qrc:/sounds/Sounds/explosionEnemy.wav");
}

Bullet::~Bullet()
{}

void Bullet::shotPlayerBullet()
{
    bulletMoveTimer = new QTimer();
    bulletMoveTimer->start(20);
    connect(bulletMoveTimer, &QTimer::timeout, this, &Bullet::movePlayerBullet);
}

void Bullet::movePlayerBullet()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i=0, n = colliding_items.size(); i < n; i++)
    {
        if (typeid(*(colliding_items[i])) == typeid(EnemyType1))
        {
            //exploSound->play();
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete colliding_items[i];
            delete this;
            qDebug() << "EnemyType1 killed to" << pos().y();
            game->playerScore->increaseScore();
            return;
        }
        if (typeid(*(colliding_items[i])) == typeid(EnemyType2))
        {
            //exploSound->play();
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete colliding_items[i];
            delete this;
            qDebug() << "EnemyType2 killed to" << pos().y();
            game->playerScore->increaseScore();
            return;
        }
        if (typeid(*(colliding_items[i])) == typeid(EnemyType3))
        {
            //exploSound->play();
            //scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            //delete colliding_items[i];
            delete this;
            qDebug() << "Bullet destroyed on EnemyType3 to" << pos().y();
            game->playerScore->increaseScore();
            return;
        }
        if (typeid(*(colliding_items[i])) == typeid(BossType1))
        {
            //exploSound->play();
            game->Boss1->decreaseBossLife();

            if (game->Boss1->getBossLife() <=0)
            {
            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];
            qDebug() << "Boss killed to" << pos().y();
            game->playerScore->setIncreaseScore(10);
            game->playerScore->bossType1Activated=false;
            }

            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    if (game->playerShip->getIsRunning() == true)
        setPos(x(), y()-10);
    if (pos().y() + pixmap().height() <= 0)
    {
        scene()->removeItem(this);
        delete this;
        qDebug() << "bullet deleted to " << pos().y();
        return;
    }

    if (game->playerShip->gameReset==true)
        delete this;
}

void Bullet::shotSpecialPlayerBullet()
{
    QTimer *specialBulletMoveTimer = new QTimer();
    specialBulletMoveTimer->start(15);

    connect(specialBulletMoveTimer, &QTimer::timeout, this , &Bullet::moveSpecialPlayerBullet);
}

void Bullet::moveSpecialPlayerBullet()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i=0, n = colliding_items.size(); i < n; i++)
    {
        if (typeid(*(colliding_items[i])) == typeid(Meteorite))
        {
            //exploSound->play();
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete colliding_items[i];
            delete this;
            qDebug() << "Bullet destroyed on a fuckin Meteorite to" << pos().y();
            return;
        }
        if (typeid(*(colliding_items[i])) == typeid(EnemyType1))
        {
            //exploSound->play();
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete colliding_items[i];
            delete this;
            qDebug() << "EnemyType1 killed to" << pos().y();
            game->playerScore->increaseScore();
            return;
        }
        if (typeid(*(colliding_items[i])) == typeid(EnemyType2))
        {
            //exploSound->play();
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete colliding_items[i];
            delete this;
            qDebug() << "EnemyType2 killed to" << pos().y();
            game->playerScore->increaseScore();
            return;
        }
        if (typeid(*(colliding_items[i])) == typeid(EnemyType3))
        {
            //exploSound->play();
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete colliding_items[i];
            delete this;
            qDebug() << "Bullet destroyed on EnemyType3 to" << pos().y();
            game->playerScore->setIncreaseScore(2);
            return;
        }
        if (typeid(*(colliding_items[i])) == typeid(BossType1))
        {
            //exploSound->play();
            game->Boss1->decreaseBossLife();
            game->Boss1->decreaseBossLife();

            if (game->Boss1->getBossLife() <=0)
            {
            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];
            qDebug() << "Boss killed to" << pos().y();
            game->playerScore->setIncreaseScore(10);
            game->playerScore->bossType1Activated=false;
            }

            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    if (game->playerShip->getIsRunning() == true)
        setPos(x(), y()-10);
    if (pos().y() + pixmap().height() <= 0)
    {
        scene()->removeItem(this);
        delete this;
        qDebug() << "bullet deleted to " << pos().y();
        return;
    }

    if (game->playerShip->gameReset==true)
        delete this;

}

void Bullet::enemyType2BulletMove()
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
            qDebug() << "EnemyType2's bullet hitted you to" << pos().y();
            return;
        }
    }

    if (game->playerShip->getIsRunning() == true)
        setPos(x(), y()+3);
    if ((pos().y() - pixmap().height() > 600) && (scene() !=0))
    {
        scene()->removeItem(this);
        delete this;
        qDebug() << "EnemyType2's bullet deleted to " << pos().y();
        return;
    }

    if (game->playerShip->gameReset==true)
        delete this;
}

void Bullet::enemyType3BulletMove()
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
            qDebug() << "EnemyType3's bullet hitted you to" << pos().y();
            return;
        }
    }

    if (game->playerShip->getIsRunning() == true)
        setPos(x(), y()+3);
    if ((pos().y() - pixmap().height() > 600) && (scene() !=0))
    {
        scene()->removeItem(this);
        delete this;
        qDebug() << "EnemyType3's bullet deleted to " << pos().y();
        return;
    }

    if (game->playerShip->gameReset==true)
        delete this;

}



void Bullet::bossFirstBulletMove()
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
            qDebug() << "Boss bullet hitted you to" << pos().y();
            return;
        }
    }

    if (game->playerShip->getIsRunning() == true)
        setPos(x(), y()+3);
    if (pos().y() - pixmap().height() > 600)
    {
        scene()->removeItem(this);
        delete this;
        qDebug() << "Boss bullet deleted to " << pos().y();
        return;
    }

    if (game->playerShip->gameReset==true)
        delete this;
}

void Bullet::bossSecondBulletMove()
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
            qDebug() << "Boss bullet hitted you to" << pos().y();
            return;
        }
    }

    if (game->playerShip->getIsRunning() == true)
        setPos(x()-1.5, y()+3);
    if (pos().y() - pixmap().height() > 600)
    {
        scene()->removeItem(this);
        delete this;
        qDebug() << "Boss bullet deleted to " << pos().y();
        return;
    }

    if (game->playerShip->gameReset==true)
        delete this;
}

void Bullet::bossThirdBulletMove()
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
            qDebug() << "Boss bullet hitted you to" << pos().y();
            return;
        }
    }

    if (game->playerShip->getIsRunning() == true)
        setPos(x()+1.5, y()+3);
    if (pos().y() - pixmap().height() > 600)
    {
        scene()->removeItem(this);
        delete this;
        qDebug() << "Boss bullet deleted to " << pos().y();
        return;
    }

    if (game->playerShip->gameReset==true)
        delete this;
}
