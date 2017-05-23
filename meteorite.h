#ifndef METEORITE_H
#define METEORITE_H

#include <QGraphicsPixmapItem>
#include <random>

using namespace std;

class Meteorite : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

    public:
        Meteorite();

        static random_device generator;

        void meteoriteSpawn();
        void move();
};

#endif // METEORITE_H
