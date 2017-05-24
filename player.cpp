#include "player.h"
#include "enemytype1.h"
#include "bullet.h"
#include "game.h"
#include "player.h"
#include "bonus.h"

#include <QDebug>
#include <QGraphicsTextItem>
#include <QApplication>

extern Game *game;

Player::Player(QGraphicsItem *parent)
      : QGraphicsPixmapItem(parent)
{
    isShooting=false;
    setPixmap(QPixmap(":/pictures/Images/playerShip1.png"));
//    bulletSound = new QMediaPlayer;
//    bulletSound->setMedia(QUrl("qrc:/sounds/Sounds/laserBullet.wav"));
}

Player::~Player()
{
    tripleBulletBonusActivated=false;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    qDebug() << Q_FUNC_INFO;
    if ((event->key() == Qt::Key_Left) && (pos().x() > 0) && (isRunning==true))
    {
        game->moveToTheLeft();
        //setPos(x()-15, y());

//        if (gameReset==true)
//        {
//            gameReset=false;
//            game->playerScore->calculLevelReached();
//            qDebug() << "On relance le jeu et les timers";
//        }
    }
    if ((event->key() == Qt::Key_Right) && (pos().x()+100 < 800) && (isRunning==true))
    {
        game->moveToTheRight();
        //setPos(x()+15, y());

//        if (gameReset==true)
//        {
//            gameReset=false;
//            game->playerScore->calculLevelReached();
//            qDebug() << "On relance le jeu et les timers";
//        }
    }
    if ((event->key() == Qt::Key_Down) && (isRunning==true))
    {
        game->stopAnyMove();
    }
    if ((event->key() == Qt::Key_Space) && (isRunning==true))
    {
        game->shotABullet();
    }
    if (event->key() == Qt::Key_P)
    {
        if (getIsRunning() == true)
            setIsRunning(false);
        else if (getIsRunning() == false)
            setIsRunning(true);
    }
    if (event->key() == Qt::Key_Escape)
    {
        game->playerGameOver->paintGameOver();
    }
    if(event->key() == Qt::Key_R)
    {
        resetGame();
    }
}

void Player::shotSomeBullets()
{
    if (specialBulletBonusActivated==true)
    {
        if (tripleBulletBonusActivated==true)
        {
            Bullet *playerSecondBullet = new Bullet();
            playerSecondBullet->setPos(x()+2, y()+10);
            playerSecondBullet->shotSpecialPlayerBullet();
            scene()->addItem(playerSecondBullet);
            playerSecondBullet->setPixmap(QPixmap(":/pictures/Images/purpleLazerBullet.png"));

            Bullet *playerThirdBullet = new Bullet();
            playerThirdBullet->setPos(x()+87, y()+10);
            playerThirdBullet->shotSpecialPlayerBullet();
            scene()->addItem(playerThirdBullet);
            playerThirdBullet->setPixmap(QPixmap(":/pictures/Images/purpleLazerBullet.png"));

            QTimer *endOfTripleBulletBonusTimer = new QTimer();
            endOfTripleBulletBonusTimer->setSingleShot(1);
            endOfTripleBulletBonusTimer->start(15000);

            connect(endOfTripleBulletBonusTimer, &QTimer::timeout, this , &Player::endOfTripleBulletBonus);
        }

        playerBullet = new Bullet();
        playerBullet->setPixmap(QPixmap(":/pictures/Images/purpleLazerBullet.png"));
        playerBullet->setPos(x()+45, y());
        playerBullet->shotSpecialPlayerBullet();
        scene()->addItem(playerBullet);

//        if (bulletSound->state() == QMediaPlayer::PlayingState)
//            bulletSound->setPosition(0);
//        else if (bulletSound->state() == QMediaPlayer::StoppedState)
//            bulletSound->play();

        QTimer *endOfSpecialBulletBonusTimer = new QTimer();
        endOfSpecialBulletBonusTimer->setSingleShot(1);
        endOfSpecialBulletBonusTimer->start(10000);

        connect(endOfSpecialBulletBonusTimer, &QTimer::timeout, this, &Player::endOfSpecialBulletBonus);
    }
    else
    {
        if (tripleBulletBonusActivated==true)
        {
            Bullet *playerSecondBullet = new Bullet();
            playerSecondBullet->setPos(x()+2, y()+10);
            playerSecondBullet->shotPlayerBullet();
            scene()->addItem(playerSecondBullet);
            playerSecondBullet->setPixmap(QPixmap(":/pictures/Images/bluLazerBullet.png"));

            Bullet *playerThirdBullet = new Bullet();
            playerThirdBullet->setPos(x()+87, y()+10);
            playerThirdBullet->shotPlayerBullet();
            scene()->addItem(playerThirdBullet);
            playerThirdBullet->setPixmap(QPixmap(":/pictures/Images/bluLazerBullet.png"));

            QTimer *endOfTripleBulletBonusTimer = new QTimer();
            endOfTripleBulletBonusTimer->setSingleShot(1);
            endOfTripleBulletBonusTimer->start(15000);

            connect(endOfTripleBulletBonusTimer, &QTimer::timeout, this , &Player::endOfTripleBulletBonus);
        }

        playerBullet = new Bullet();
        playerBullet->setPixmap(QPixmap(":/pictures/Images/greenLazerBullet.png"));
        playerBullet->setPos(x()+45, y());
        playerBullet->shotPlayerBullet();
        scene()->addItem(playerBullet);

//        if (bulletSound->state() == QMediaPlayer::PlayingState)
//            bulletSound->setPosition(0);
//        else if (bulletSound->state() == QMediaPlayer::StoppedState)
//            bulletSound->play();
    }
}

bool Player::getIsRunning()
{
    return isRunning;
}

void Player::setIsRunning(bool b)
{
    isRunning=b;
}

void Player::resetGame()
{
    setIsRunning(true);
    game->playerScore->setScore(0);
    game->playerLife->setLife(3);
    game->playerGameOver->paintNothing();
    game->playerShip->setPos(350,500);
    gameReset=true;
    game->playerScore->tutoActivated=false;
    game->playerScore->level1Activated=false;
    game->playerScore->level2Activated=false;
    game->playerScore->level3Activated=false;
    game->playerScore->level4Activated=false;
    game->playerScore->bonusSpawn=false;
    game->playerScore->meteoriteActivated=false;
    game->playerScore->bossType1Activated=false;
    game->playerShip->tripleBulletBonusActivated=false;
    game->playerShip->specialBulletBonusActivated=false;
    game->tripleBulletBonusSpawnTimer->stop();
    game->lifeBonusSpawnTimer->stop();
    game->meteoriteSpawnTimer->stop();
    game->specialBulletBonusSpawnTimer->stop();
    game->enemyType1SpawnTimer->stop();
    game->enemyType2SpawnTimer->stop();
    game->enemyType3SpawnTimerL->stop();
    game->enemyType3SpawnTimerR->stop();
    qDebug() << "Halala super le jeu est rest";
}

void Player::endOfTripleBulletBonus()
{
    tripleBulletBonusActivated=false;
}

void Player::endOfSpecialBulletBonus()
{
    specialBulletBonusActivated=false;
}
