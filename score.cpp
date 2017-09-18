#include "score.h"
#include "game.h"

#include <QFont>
#include <QDebug>

extern Game *game;

random_device Score::generator{};

Score::Score(QGraphicsItem *parent)
     :QGraphicsTextItem(parent)
{
    score = 0;
    life = 3;
}

Score::~Score()
{}

int Score::random(int b1, int b2)
{
    uniform_int_distribution<int> distribution(b1,b2);
    int random_number = distribution(generator);

    return random_number;
}

void Score::increaseScore()
{
    score++;
    repaintScore();
    calculLevelReached();
}

void Score::setIncreaseScore(int i_score)
{
    score+=i_score;
    repaintScore();
    calculLevelReached();
}

void Score::setScore(int _score)
{
    score=_score;
    repaintScore();
}

void Score::repaintScore()
{
    setPlainText(QString("Score : " + QString::number(score)));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("karmatic arcade",15));
}

int Score::getScore()
{
    return score;
}

void Score::decreaseLife()
{
    life=life-1;
    repaintLife();
}

void Score::increaseLife()
{
    life++;
    repaintLife();
}

void Score::setIncreaseLife(int _life)
{
    life+=_life;
    repaintLife();
}

void Score::setLife(int s_life)
{
    life = s_life;
    repaintLife();
}

void Score::repaintLife()
{
    setPlainText(QString("Life : " + QString::number(life)));
    setDefaultTextColor(Qt::red);
    setFont(QFont("Karmatic arcade",15));
}

int Score::getLife()
{
    return life;
}

void Score::paintRules()
{
    setPlainText(QString("Ce que vous savez ! \n\n"
                         "-Tirez aec la touche espace\n"
                         "-Utilisez les fleches droite gauche\n"
                         " pour vous deplacer\n"
                         "-La fleche du bas immobilise le vaisseau\n"
                         "-Vous perdez 1 pdv en cas de colision\n"
                         "-Vous perdez 1 pdv si on vaisseau enemi \n depasse le bas de l'écran"));
    setDefaultTextColor(Qt::yellow);
    setFont(QFont("Karmatic arcade",15));
    rulesDisplayed=true;
}

void Score::paintGameOver()
{
    game->playerRules->paintNothing();
    setPlainText(QString("Game Over"));
    setDefaultTextColor(Qt::green);
    setFont(QFont("Karmatic arcade",50));
    qDebug() << "On affiche GAME OVER";
}

void Score::paintNothing()
{
    setPlainText(QString(""));
}

void Score::calculLevelReached()  //gestion des niveaux et de la difficulté de jeu
{
    if ((getScore() <= 5) && (tutoActivated==false))
    {
        qDebug() << "TUTORIEL TADA";
        game->enemyType1SpawnTimer->start(2000);
        tutoActivated=true;
    }

    if ((getScore() > 5) && (level1Activated==false))
    {
        qDebug() << "LEVEL 1";
        game->enemyType1SpawnTimer->start(1100);
        level1Activated=true;
    }

    if ((getScore() >= 10) && (bonusSpawn==false))
    {
        game->tripleBulletBonusSpawnTimer->start(random(10000,50000));
        game->lifeBonusSpawnTimer->start(random(10000,40000));
        bonusSpawn=true;
    }

    if ((getScore() >= 40 ) && (level2Activated==false))
    {
        qDebug() << "LEVEL 2 REACHED";
        game->setEnemyType2B1(2000);
        game->setEnemyType2B2(10000);
        game->funcEnemyType2Spawn();
        game->enemyType1SpawnTimer->start(1500);
        game->specialBulletBonusSpawnTimer->start(random(15000,60000));
        level2Activated=true;
    }

    if ((getScore() >= 50) && (meteoriteActivated==false))
    {
        qDebug() << "METEORITE INCOMING";
        game->specialBulletBonusSpawnTimer->start(random(10000,50000));
        game->b1meteoritespawn=15000;
        game->b2meteoritespawn=25000;
        game->funcMeteoriteSpawn();
        meteoriteActivated=true;
    }

    if ((getScore() >= 75) && (level3Activated==false))
    {
        qDebug() << "LEVEL 3 REACHED";
        game->setEnemyType2B1(5000);
        game->setEnemyType2B2(8000);
        //game->funcEnemyType2Spawn();
        game->enemyType1SpawnTimer->start(2500);
        level3Activated=true;
    }

    if ((getScore() >= 2 ) && (meteoriteActivated==false))
    {
        qDebug() << "METEORITE INCOMING";
        game->enemyType1SpawnTimer->stop();
        game->enemyType2SpawnTimer->stop();
        game->b1meteoritespawn=1000;
        game->b2meteoritespawn=2000;
        game->funcMeteoriteSpawn();
        meteoriteActivated=true;
    }

    if ((getScore() == 100) && (bossType1Activated==false))
    {
        qDebug() << "BOSS INCOMING !!!!!!!!!!!!!!!!";
        game->funcBossType1Spawn();
        bossType1Activated=true;
    }

    if ((getScore() >= 115 ) && (level4Activated==false))
    {
        qDebug() << "LEVEL 4 REACHED";
        game->enemyType1SpawnTimer->stop();
        game->enemyType2SpawnTimer->stop();

        game->funcEnemyType3SpawnL();
        game->enemyType3SpawnTimerR->start(8000);
        level4Activated=true;
    }

    if((getScore() >= 160) && (level5Activated==false))
    {
        qDebug() << "LEVEL 5 REACHED";
        game->enemyType3SpawnTimerL->stop();
        game->enemyType3SpawnTimerR->stop();
        game->setEnemyType2B1(4000);
        game->setEnemyType2B2(12000);
        game->funcEnemyType2Spawn();
        game->enemyType1SpawnTimer->start(2000);
        level5Activated=true;
    }
}
