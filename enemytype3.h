#ifndef ENEMYTYPE3_H
#define ENEMYTYPE3_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <random>

using namespace std;

class EnemyType3 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    private:
        int speedDifficulty;
        bool rightSide;

    public:
        EnemyType3();
        ~EnemyType3();

        static random_device generator;

        int dep;
        void enemySpawn(int _dep);
        void move();
        void shotBullet();

        int getSpeedDifficulty();
        void setSpeedDifficulty(int speed_D);

        bool getRightSide();
        void setRightSide(bool b);
};

#endif // ENEMYTYPE3_H
