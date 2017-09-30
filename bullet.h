#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <random>
#include <QMediaPlayer>

using namespace std;

class Bullet : public QObject, public QGraphicsPixmapItem
{

    Q_OBJECT

    private:
        QMediaPlayer *exploSound;

    public:
        Bullet();
        ~Bullet();

        static random_device generator;

        QTimer *bulletMoveTimer;
        void shotPlayerBullet();
        void movePlayerBullet();

        void shotSpecialPlayerBullet();
        void moveSpecialPlayerBullet();

        void enemyType2BulletMove();
        //void enemyType3BulletMove() ;

        void bossFirstBulletMove();
        void bossSecondBulletMove();
        void bossThirdBulletMove();
};

#endif // BULLET_H
