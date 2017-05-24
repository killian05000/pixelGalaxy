#include "enemytype2.h"
#include "bullet.h"
#include "game.h"
#include "player.h"

#include <QGraphicsScene>
#include <QDebug>
#include <typeinfo>
#include <QList>

extern Game *game;

random_device EnemyType2::generator{};

EnemyType2::EnemyType2()
    : QObject(), QGraphicsPixmapItem()
{
    speedDifficulty=30;
}

EnemyType2::~EnemyType2()
{}

int EnemyType2::getSpeedDifficulty()
{
    return speedDifficulty;
}

void EnemyType2::setSpeedDifficulty(int speed_D)
{
    speedDifficulty=speed_D;
}

void EnemyType2::enemySpawn()
{
    uniform_int_distribution<int> distribution(0,700);
    int random_number = distribution(generator);
    setPos(random_number, -pixmap().height());

    QTimer *enemyMoveTimer = new QTimer();
    enemyMoveTimer->start(speedDifficulty);

    QTimer *enemyBulletTimer = new QTimer();
    enemyBulletTimer->start(1500);

    if (game->playerLife->getLife() <= 0)
    {
       enemyMoveTimer->setSingleShot(1);
       enemyBulletTimer->setSingleShot(1);
       qDebug() <<"enemyType2 Timers singleShoted";
    }

    connect(enemyMoveTimer, &QTimer::timeout, this, &EnemyType2::move);
    connect(enemyBulletTimer, &QTimer::timeout, this, &EnemyType2::shotBullet);
}

void EnemyType2::move()
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
            qDebug() << "EnemyType2 item colision to " << pos().y();
            return;
        }
    }
    if (game->playerShip->getIsRunning() == true)
        setPos(x(), y()+2);

    if ((game->playerLife->getLife() <= 0) && (game->playerShip->getIsRunning()== true))
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
        qDebug() << "EnemyType2 deleted to " << pos().y();
        if(game->playerLife->getLife() > 0)
            game->playerLife->decreaseLife();
    }

    if (game->playerShip->gameReset==true)
         delete this;
}

void EnemyType2::shotBullet()
{
    if ((game->playerLife->getLife() > 0) && (game->playerShip->getIsRunning()==true))
    {
        Bullet *enemyBullet = new Bullet();
        enemyBullet->setPixmap(QPixmap(":/pictures/Images/redLazerBullet.png"));
        enemyBullet->setPos((x()+pixmap().width()/2), y()+pixmap().height());
        scene()->addItem(enemyBullet);

        QTimer *enemyBulletSpeed = new QTimer();
        enemyBulletSpeed->start(15);

        connect(enemyBulletSpeed, &QTimer::timeout, enemyBullet, &Bullet::enemyType2BulletMove);
    }
}
