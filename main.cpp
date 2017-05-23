#include "game.h"

Game *game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game g;
    game = &g;

    return a.exec();
}
