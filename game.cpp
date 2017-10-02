#include "game.h"
#include "player.h"
#include "bullet.h"
#include "enemytype1.h"
#include "enemytype2.h"
#include "enemytype3.h"
#include "bonus.h"
#include "score.h"
#include "meteorite.h"
#include "bosstype1.h"

#include <QDebug>
#include <QBrush>
#include <QImage>
#include <QTimer>
#include <QDesktopWidget>
#include <QSize>
#include <QPixmap>

random_device Game::generator{};

extern Game *game;

Game::Game(QWidget *parent)
    : QGraphicsView(parent)
{
    screenWidth = QApplication::desktop()->width();
    screenHeight = QApplication::desktop()->height();

    qDebug() << screenWidth << " / " << screenHeight;

    playerShip = new Player();
    playerShip->setFlag(QGraphicsItem::ItemIsFocusable);
    playerShip->setFocus();

    playerScore = new Score();
    playerScore->setPos(screenHeight/40, screenWidth/14);
    playerScore->repaintScore();
    playerLife = new Score();
    //playerLife->setPos(playerScore->x(), playerScore->y()+25);
    playerLife->setPos(playerScore->x(),screenWidth/9);
    playerLife->repaintLife();
    playerRules = new Score();
    playerRules->setPos(screenWidth/3, screenHeight/4);
    playerGameOver = new Score();
    playerGameOver->setPos(screenWidth/4, screenHeight/3);

//    moveLeftButton = new Button();
//    moveLeftButton->setRect(scene->width()/4,0,scene->width()/2,scene->height());
//    moveLeftButton->setPen(QPen(Qt::red,2));
    //moveLeftButton->hide();
    moveRightButton = new Button();
    moveRightButton->setRect(400,450,400,150);
    //moveRightButton->setPen(QPen(Qt::blue,2));
    moveRightButton->hide();
    shotButton = new Button();
    shotButton->setRect(0,0,800,450);
    //shotButton->setPen(QPen(Qt::green,2));
    shotButton->hide();

    enemy1 = new EnemyType1();
    enemy2 = new EnemyType2();
    Boss1 = new BossType1();

    QPixmap backg = QPixmap(":/pictures/Images/background1.jpg");
    backg=backg.scaled(QSize(screenWidth,screenHeight),Qt::IgnoreAspectRatio);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,screenWidth,screenHeight);
    scene->setBackgroundBrush(QBrush(backg));
    //scene->setSceneRect(0,0,800,600);
    //scene->setBackgroundBrush(QBrush(QImage(":/pictures/Images/background1.jpg")));
    scene->addItem(playerShip);
    scene->addItem(playerScore);
    scene->addItem(playerLife);
    scene->addItem(playerRules);
    //scene->addItem(moveLeftButton);
    scene->addItem(moveRightButton);
    scene->addItem(shotButton);

    view = new QGraphicsView(scene);
    view->show();
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->showMaximized();
    //view->setFixedSize(800,600);
    //view->setBackgroundBrush(QBrush(QImage(":/pictures/Images/background3.png")));

    //playerShip->setPos(((view->width()-playerShip->pixmap().width())/2), (view->height() - playerShip->pixmap().height()));
    playerShip->setPos((screenWidth+-playerShip->pixmap().width())/2,screenHeight-playerShip->pixmap().height());

    moveLeftButton = new Button();
    moveLeftButton->setRect(scene->width()/4,0,scene->width()/2,scene->height());
    moveLeftButton->setPen(QPen(Qt::red,2));
    scene->addItem(moveLeftButton);

    lifeBonusSpawnTimer = new QTimer(this);
    tripleBulletBonusSpawnTimer = new QTimer(this);
    specialBulletBonusSpawnTimer = new QTimer(this);
    enemyType1SpawnTimer = new QTimer(this);
    enemyType2SpawnTimer = new QTimer(this);
    enemyType3SpawnTimerL = new QTimer(this);
    enemyType3SpawnTimerR = new QTimer(this);
    meteoriteSpawnTimer = new QTimer(this);

    moveToTheLeftTimer = new QTimer(this);
    moveToTheRightTimer = new QTimer(this);

    connect(enemyType1SpawnTimer, &QTimer::timeout, this, &Game::funcEnemySpawn);
    connect(enemyType2SpawnTimer, &QTimer::timeout, this, &Game::funcEnemyType2Spawn);
    connect(enemyType3SpawnTimerL, &QTimer::timeout, this, &Game::funcEnemyType3SpawnL);
    connect(enemyType3SpawnTimerR, &QTimer::timeout, this, &Game::funcEnemyType3SpawnR);

    connect(meteoriteSpawnTimer, &QTimer::timeout, this, &Game::funcMeteoriteSpawn);
    connect(lifeBonusSpawnTimer, &QTimer::timeout, this, &Game::funcLifeBonusSpawn);
    connect(tripleBulletBonusSpawnTimer, &QTimer::timeout, this , &Game::funcTripleBulletBonusSpawn);
    connect(specialBulletBonusSpawnTimer, &QTimer::timeout, this, &Game::funcSpecialBulletBonusSpawn);

    connect(moveLeftButton, &Button::clicked, this, &Game::moveToTheLeft);
    connect(moveRightButton, &Button::clicked, this, &Game::moveToTheRight);
    connect(shotButton, &Button::clicked, this, &Game::shotABullet);


    backgroundMusic= new QMediaPlayer();
    backgroundMusic->setMedia(QUrl("qrc:/sounds/Sounds/backgroundMusic.wav"));
    backgroundMusic->play();
    connect(backgroundMusic, &QMediaPlayer::stateChanged, this, &Game::loopBackgroundMusic);
}

Game::~Game()
{}

void Game::setEnemyType2B1(int b)
{
    b1=b;
}

int Game::getEnemyType2B1()
{
    return b1;
}

void Game::setEnemyType2B2(int b)
{
    b2=b;
}

int Game::getEnemyType2B2()
{
    return b2;
}

void Game::loopBackgroundMusic()
{
    backgroundMusic->play();
}

void Game::moveToTheLeft()
{
    if (game->playerScore->getScore()==0)
        game->playerScore->calculLevelReached();

    if (game->playerShip->gameReset==true)
    {
        game->playerShip->gameReset=false;
        game->playerScore->calculLevelReached();
        qDebug() << "On relance le jeu et les timers";
    }

    if (moveToTheRightTimer->isActive())
    {
        moveToTheRightTimer->stop();
        disconnect(moveToTheRightTimer, &QTimer::timeout, this, &Game::funcMoveRight);
    }

    if(!moveToTheLeftTimer->isActive())
    {
        moveToTheLeftTimer->start(7);
        connect(moveToTheLeftTimer, &QTimer::timeout, this, &Game::funcMoveLeft);
    }

    if(game->playerShip->getIsRunning()==false)
    {
        moveToTheLeftTimer->stop();
        disconnect(moveToTheLeftTimer, &QTimer::timeout, this, &Game::funcMoveRight);
    }
}

void Game::moveToTheRight()
{
    if (game->playerScore->getScore()==0)
        game->playerScore->calculLevelReached();

    if (game->playerShip->gameReset==true)
    {
        game->playerShip->gameReset=false;
        game->playerScore->calculLevelReached();
        qDebug() << "On relance le jeu et les timers";
    }

    if (moveToTheLeftTimer->isActive())
    {
        moveToTheLeftTimer->stop();
        disconnect(moveToTheLeftTimer, &QTimer::timeout, this, &Game::funcMoveLeft);
    }

    if(!moveToTheRightTimer->isActive())
    {
        moveToTheRightTimer->start(7);
        connect(moveToTheRightTimer, &QTimer::timeout, this, &Game::funcMoveRight);
    }

    if(game->playerShip->getIsRunning()==false)
    {
        moveToTheRightTimer->stop();
        disconnect(moveToTheRightTimer, &QTimer::timeout, this, &Game::funcMoveRight);
    }
}

void Game::shotABullet()
{
//    if (moveToTheLeftTimer->isActive())
//    {
//        moveToTheLeftTimer->stop();
//        disconnect(moveToTheLeftTimer, &QTimer::timeout, this, &Game::funcMoveLeft);
//    }
//    if (moveToTheRightTimer->isActive())
//    {
//        moveToTheRightTimer->stop();
//        disconnect(moveToTheRightTimer, &QTimer::timeout, this, &Game::funcMoveRight);
//    }
    game->playerShip->shotSomeBullets();
}

void Game::stopAnyMove()
{
    if (moveToTheLeftTimer->isActive())
    {
        moveToTheLeftTimer->stop();
        disconnect(moveToTheLeftTimer, &QTimer::timeout, this, &Game::funcMoveLeft);
    }
    if (moveToTheRightTimer->isActive())
    {
        moveToTheRightTimer->stop();
        disconnect(moveToTheRightTimer, &QTimer::timeout, this, &Game::funcMoveRight);
    }
}


void Game::funcEnemyType2Spawn()
{
    if (((game->playerLife->getLife() >0) && (game->playerShip->getIsRunning() == true)) && (game->playerScore->bossType1Activated==false))
    {
        EnemyType2 *enemyT2= new EnemyType2();
        scene->addItem(enemyT2);
        enemyT2->enemySpawn();

        uniform_int_distribution<int> distribution(getEnemyType2B1(),getEnemyType2B2());
        int random_number = distribution(generator);

        enemyType2SpawnTimer->start(random_number);
    }
}

void Game::funcEnemyType3SpawnL()
{
    EnemyType3 *enemyT3= new EnemyType3();
    scene->addItem(enemyT3);
    enemyT3->enemySpawn(0);

    enemyType3SpawnTimerL->start(1500);
}

void Game::funcEnemyType3SpawnR()
{
    EnemyType3 *enemyT3= new EnemyType3();
    scene->addItem(enemyT3);
    enemyT3->enemySpawn(1);

    enemyType3SpawnTimerR->start(1500);
}

void Game::funcBossType1Spawn()
{
    BossType1 *Boss1 = new BossType1();
    Boss1->setPixmap(QPixmap(":/pictures/Images/bossType1.png"));

    scene->addItem(Boss1);
    Boss1->bossType1Spawn();
    qDebug() << "A BOSS HAVE BEEN CREATED ---TAKE HIM DOWN !!!!---";
}

void Game::funcMeteoriteSpawn()
{
    if ((game->playerLife->getLife() > 0) && (game->playerShip->getIsRunning() == true))
    {
        Meteorite *meteorite = new Meteorite();

        uniform_int_distribution<int> distribution_skin(1,5);
        int random_skin = distribution_skin(generator);

        if (random_skin <= 2)
            meteorite->setPixmap(QPixmap(":/pictures/Images/meteorite2.png"));
        else if (random_skin <= 4)
            meteorite->setPixmap(QPixmap(":/pictures/Images/meteorite3.png"));
        else if (random_skin = 5)
            meteorite->setPixmap(QPixmap(":/pictures/Images/meteorite4.png"));

        scene->addItem(meteorite);
        meteorite->meteoriteSpawn();
        qDebug() << "A meteorite have been created  ---ARMAGEDON---";

        uniform_int_distribution<int> distribution(b1meteoritespawn,b2meteoritespawn);
        int random_number = distribution(generator);

        meteoriteSpawnTimer->start(random_number);
    }

}

void Game::funcLifeBonusSpawn()
{
    if ((game->playerLife->getLife() > 0) && (game->playerShip->getIsRunning() == true))
    {
        Bonus *lifeBonus = new Bonus();
        lifeBonus->setPixmap(QPixmap(":/pictures/Images/lifeBonus.png"));

        scene->addItem(lifeBonus);
        lifeBonus->heartSpawn();

        uniform_int_distribution<int> distribution(5000,18000);
        int random_number = distribution(generator);

        lifeBonusSpawnTimer->start(random_number);
    }
}

void Game::funcTripleBulletBonusSpawn()
{
    if ((game->playerLife->getLife() > 0) && (game->playerShip->getIsRunning() == true))
    {
        Bonus *tripleBulletBonus = new Bonus();
        tripleBulletBonus->setPixmap(QPixmap(":/pictures/Images/tbBonus.png"));

        scene->addItem(tripleBulletBonus);
        tripleBulletBonus->tripleBulletSpawn();

        uniform_int_distribution<int> distribution(70000,90000);
        int random_number = distribution(generator);

        tripleBulletBonusSpawnTimer->start(random_number);
    }

}

void Game::funcSpecialBulletBonusSpawn()
{
    if ((game->playerLife->getLife() > 0) && (game->playerShip->getIsRunning() == true))
    {
        Bonus *specialBulletBonus = new Bonus();
        specialBulletBonus->setPixmap(QPixmap(":/pictures/Images/sbBonus.png"));

        scene->addItem(specialBulletBonus);
        specialBulletBonus->specialBulletSpawn();

        uniform_int_distribution<int> distribution(50000,70000);
        int random_number = distribution(generator);

        specialBulletBonusSpawnTimer->start(random_number);
    }

}

void Game::funcMoveLeft()
{
    if ((game->playerShip->x() >= game->scene->width()/4) && (game->playerShip->getIsRunning()==true))
        game->playerShip->setPos(playerShip->x()-3.3, playerShip->y());
}

void Game::funcMoveRight()
{
    if ((game->playerShip->x() <= (game->scene->width()-game->scene->width()/4) - game->playerShip->pixmap().width()) && (game->playerShip->getIsRunning()==true))
        game->playerShip->setPos(playerShip->x()+3.3, playerShip->y());
}

void Game::funcEnemySpawn()
{
    if (((game->playerLife->getLife() > 0) && (game->playerShip->getIsRunning() == true))  && (game->playerScore->bossType1Activated==false)) //&& (game->playerScore->level2Possible == true))
    {
        EnemyType1 *enemy = new EnemyType1();

        scene->addItem(enemy);
        enemy->enemySpawn();
    }
}
