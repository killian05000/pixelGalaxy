#ifndef BONUS_H
#define BONUS_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <random>

using namespace std;

class Bonus : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

    public:

        Bonus();
        ~Bonus();

        static random_device generator;

        void heartSpawn();
        void moveHeartBonus();

        void tripleBulletSpawn();
        void moveTripleBulletBonus();

        void specialBulletSpawn();
        void moveSpecialBulletBonus();
};


#endif // BONUS_H
