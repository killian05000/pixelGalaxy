#ifndef GAME_H
#define GAME_H


#include "player.h"
#include "enemytype1.h"
#include "score.h"
#include "bosstype1.h"
#include "enemytype2.h"
#include "bonus.h"
#include "button.h"

#include <QApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QTimer>
#include <QMediaPlayer>
#include <random>
#include <QGraphicsRectItem>

using namespace std;

class Game : public QGraphicsView
{
    Q_OBJECT

    private :
        int b1=0;
        int b2=0;
        QMediaPlayer *backgroundMusic;

    public slots:
        void funcEnemySpawn();
        void funcEnemyType2Spawn();
        void funcEnemyType3SpawnL();
        void funcEnemyType3SpawnR();
        void funcBossType1Spawn();

        void funcMeteoriteSpawn();
        void funcLifeBonusSpawn();
        void funcTripleBulletBonusSpawn();
        void funcSpecialBulletBonusSpawn();

        void funcMoveLeft();
        void funcMoveRight();

    public:

        static random_device generator;
        Game(QWidget *parent = 0);
        ~Game();

        QGraphicsScene *scene;
        QGraphicsView *view;
        Player *playerShip;
        EnemyType1 *enemy1;
        EnemyType2 *enemy2;
        BossType1 *Boss1;

        QTimer *enemyType1SpawnTimer;
        QTimer *enemyType2SpawnTimer;
        QTimer *enemyType3SpawnTimerL;
        QTimer *enemyType3SpawnTimerR;

        QTimer *meteoriteSpawnTimer;
        QTimer *lifeBonusSpawnTimer;
        QTimer *tripleBulletBonusSpawnTimer;
        QTimer *specialBulletBonusSpawnTimer;

        Score *playerScore;
        Score *playerLife;
        Score *playerGameOver;

        Bonus *bonus;

        void setEnemyType2B1(int b);
        int getEnemyType2B1();
        void setEnemyType2B2(int b);
        int getEnemyType2B2();

        void loopBackgroundMusic();

        Button *moveLeftButton;
        Button *moveRightButton;
        Button *shotButton;

        QTimer *moveToTheLeftTimer;
        void moveToTheLeft();
        QTimer *moveToTheRightTimer;
        void moveToTheRight();
        void shotABullet();
        void stopAnyMove();
};

#endif // GAME_H
