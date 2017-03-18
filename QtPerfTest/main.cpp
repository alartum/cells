#include "gameview.h"
#include <QApplication>
#include <QDebug>

int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
    GameView game;
    game.start();
    return app.exec();
}
