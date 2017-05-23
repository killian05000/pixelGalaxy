#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include <random>

using namespace std;

class Score : public QGraphicsTextItem
{
    private:
        int score;
        int life;

    public:
        Score(QGraphicsItem *parent=0);
        ~Score();

        static random_device generator;

        int random(int b1, int b2);

        void increaseScore();
        void setIncreaseScore(int i_score);
        void setScore(int _score);

        void repaintScore(); // paint ou repaint le score
        int getScore();

        void decreaseLife();
        void increaseLife();
        void setIncreaseLife(int _life);
        void setLife(int s_life);

        void repaintLife(); // paint ou repaint la vie
        int getLife();

        void paintGameOver();
        void paintNothing();

        void calculLevelReached();
        bool tutoActivated = false;
        bool level1Activated = false;
        bool bonusSpawn = false;
        bool level2Activated = false;
        bool meteoriteActivated = false;
        bool level3Activated = false;
        bool level4Activated = false;
        bool level5Activated = false;
        bool bossType1Activated= false;
};

#endif // SCORE_H
