#include "enemytype1.h"
#include "bullet.h"
#include "game.h"
#include "player.h"

#include <QGraphicsScene>
#include <QDebug>
#include <typeinfo>
#include <QList>

extern Game *game;

random_device EnemyType1::generator{};

EnemyType1::EnemyType1()
    : QObject(), QGraphicsPixmapItem()
{}

EnemyType1::~EnemyType1()
{}

int EnemyType1::getSpeedDifficulty()
{
    return speedDifficulty;
}

void EnemyType1::setSpeedDifficulty(int speed_D)
{
    speedDifficulty=speed_D;
}

void EnemyType1::enemySpawn()
{
    uniform_int_distribution<int> distribution(0,700);
    int random_number = distribution(generator);
    setPos(random_number, -100);


    if (game->playerScore->getScore() < 10)
        setSpeedDifficulty(30);
    else if ((game->playerScore->getScore() >= 10) && (game->playerScore->getScore() < 20))
        setSpeedDifficulty(25);
    else if ((game->playerScore->getScore() >= 20) && (game->playerScore->getScore() < 30))
        setSpeedDifficulty(22);
    else if ((game->playerScore->getScore() >= 30))
        setSpeedDifficulty(20);

    if (game->playerScore->level2Activated==true)
        setSpeedDifficulty(22);



    enemyMoveTimer = new QTimer();
    enemyMoveTimer->start(speedDifficulty);

    if (game->playerLife->getLife() <= 0)
    {
        enemyMoveTimer->setSingleShot(1);
        qDebug() <<"enemyType1 Timer singleShoted";
    }

    connect(enemyMoveTimer, &QTimer::timeout, this, &EnemyType1::move);
}

void EnemyType1::move()
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
            qDebug() << "EnemyType1 item colision to " << pos().y();
            return;
        }
    }
    if (game->playerShip->getIsRunning() == true)
        setPos(x(), y()+5);

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
        qDebug() << "EnemyType1 deleted to " << pos().y();
        if(game->playerLife->getLife() > 0)
            game->playerLife->decreaseLife();
    }

    if (game->playerShip->gameReset==true)
         delete this;
}
