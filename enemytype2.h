#ifndef ENEMYTYPE2_H
#define ENEMYTYPE2_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <random>

using namespace std;

class EnemyType2 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    private:
        int speedDifficulty=0;

    public:
        EnemyType2();
        ~EnemyType2();

        static random_device generator;

        void enemySpawn();
        void move();
        void shotBullet();

        int getSpeedDifficulty();
        void setSpeedDifficulty(int speed_D);
};

#endif // ENEMYTYPE2_H
