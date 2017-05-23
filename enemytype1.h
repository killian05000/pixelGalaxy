#ifndef ENEMYTYPE1_H
#define ENEMYTYPE1_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <random>

using namespace std;

class EnemyType1 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    private:
        int speedDifficulty=0;

    public:

        static random_device generator;

        EnemyType1();
        ~EnemyType1();

        void enemySpawn();
        void move();

        QTimer *enemyMoveTimer;
        int getSpeedDifficulty();
        void setSpeedDifficulty(int speed_D);
};

#endif // ENEMYTYPE1_H
