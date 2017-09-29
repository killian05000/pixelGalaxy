#ifndef PLAYER_H
#define PLAYER_H

#include "bullet.h"

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QObject>
#include <QMediaPlayer>
#include <QTimer>

class Player : public QObject, public QGraphicsPixmapItem
{

    Q_OBJECT

    private:
        bool isRunning=true;
        bool canShot=true;
        QMediaPlayer *bulletSound;

    public:
        Player(QGraphicsItem *parent=0);
        ~Player();

        Bullet *playerBullet;

        void keyPressEvent(QKeyEvent *event);
        void shotSomeBullets();

        bool getIsRunning();
        void setIsRunning(bool b);

        bool isShooting=false;

        void resetGame();
        bool gameReset=false;

        bool tripleBulletBonusActivated=false;
        void endOfTripleBulletBonus();

        bool specialBulletBonusActivated=false;
        void endOfSpecialBulletBonus();
};

#endif // PLAYER_H
