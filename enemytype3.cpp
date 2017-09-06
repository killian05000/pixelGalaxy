#include "enemytype3.h"
#include "bullet.h"
#include "game.h"

#include <typeinfo>

extern Game *game;

random_device EnemyType3::generator{};

EnemyType3::EnemyType3()
          :QObject(), QGraphicsPixmapItem()
{
    speedDifficulty=0;
    rightSide=false;
    dep=0;
}

EnemyType3::~EnemyType3()
{}

int EnemyType3::getSpeedDifficulty()
{
    return speedDifficulty;
}

void EnemyType3::setSpeedDifficulty(int speed_D)
{
    speedDifficulty=speed_D;
}

bool EnemyType3::getRightSide()
{
    return rightSide;
}

void EnemyType3::setRightSide(bool b)
{
    rightSide=b;
}

void EnemyType3::enemySpawn(int _dep)
{
    dep=_dep;
    if (dep==0)
        setPos(0, -pixmap().height());
    else if (dep==1)
        setPos(800-pixmap().width(), -pixmap().height());


    setSpeedDifficulty(10);

    QTimer *enemyMoveTimer = new QTimer;
    enemyMoveTimer->start(speedDifficulty);

    uniform_int_distribution<int> distribution(1000,2000);
    int random_number = distribution(generator);

    QTimer *enemyBulletTimer = new QTimer();
    enemyBulletTimer->start(random_number);

    if (game->playerLife->getLife() <= 0)
    {
       enemyMoveTimer->setSingleShot(1);
       enemyBulletTimer->setSingleShot(1);
       game->enemyType3SpawnTimerL->setSingleShot(1);
       game->enemyType3SpawnTimerR->setSingleShot(1);
       //qDebug() <<"enemyType3 Timers stopped";
    }

    connect(enemyMoveTimer, &QTimer::timeout, this, &EnemyType3::move);
    connect(enemyBulletTimer, &QTimer::timeout, this, &EnemyType3::shotBullet);
}

void EnemyType3::move()
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
            qDebug() << "EnemyType3 item colision to " << pos().y();
            return;
        }
    }

    if (game->playerShip->getIsRunning() == true)
    {
        if ((pos().y() <= 130) && (dep==0))
            setPos(x()+1, y()+3);
        else if ((pos().y() > 130) && (dep==0))
            setPos(x()+2, y()+0.5);

        if ((pos().y() <= 130) && (dep==1))
            setPos(x()-1, y()+3);
        else if ((pos().y() > 130) && (dep==1))
            setPos(x()-2, y()+0.5);
    }

    if ((game->playerLife->getLife() <= 0) && (game->playerShip->getIsRunning()== true))
    {
        game->playerGameOver->paintGameOver();
        scene()->addItem(game->playerGameOver);
        qDebug() << "On paralyse l'écran";
        game->playerShip->setIsRunning(false);
        return;
    }

     if ((pos().y() - pixmap().height() >= 600) || (pos().x()-pixmap().height() > 700) || (pos().x()+pixmap().height() < 0))
    {
        scene()->removeItem(this);
        delete this;
        qDebug() << "EnemyType3 deleted to " << pos().x();
        game->playerScore->increaseScore();
//        if(game->playerLife->getLife() > 0)
//            game->playerLife->decreaseLife();
    }

    if (game->playerShip->gameReset==true)
         delete this;
}

void EnemyType3::shotBullet()
{
    if ((game->playerLife->getLife() > 0) && (game->playerShip->getIsRunning()==true))
    {
        Bullet *enemyBullet = new Bullet();
        enemyBullet->setPixmap(QPixmap(":/pictures/Images/redLazerBullet.png"));
        enemyBullet->setPos((x()+pixmap().width()/2) , y()+pixmap().height());
        scene()->addItem(enemyBullet);

        QTimer *enemyBulletSpeed = new QTimer();
        enemyBulletSpeed->start(10);

        connect(enemyBulletSpeed, &QTimer::timeout, enemyBullet, &Bullet::enemyType3BulletMove);
    }
}
