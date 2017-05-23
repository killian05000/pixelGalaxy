#ifndef BOSSTYPE1_H
#define BOSSTYPE1_H

#include "bullet.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <random>

using namespace std;

class BossType1 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

    private:
        int bossLife;

    public:
        BossType1();
        ~BossType1();

        static random_device generator;

        void bossType1Spawn();
        void move();

        void shotFirstBullet();
        void shotSecondBullet();
        void shotThirdBullet();

        void decreaseBossLife();
        int getBossLife();

        int bm1;
        int bm2;
        int bm3;
};

#endif // BOSSTYPE1_H
