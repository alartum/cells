#include "gameview.h"
#include <QDebug>

GameView::GameView(QWidget *parent) :
    QGraphicsView(parent)
{
    gameScene = new GameScene;
    setScene(gameScene);
    setCacheMode(QGraphicsView::CacheBackground);
    setRenderHint(QPainter::Antialiasing, false);
    setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setFixedSize(gameScene->getSize());
    connect (&timer, SIGNAL(timeout()), gameScene, SLOT(advance()));
}

GameView::~GameView()
{
    delete gameScene;
}

void GameView::start(int msec)
{
    show();
    timer.start(msec);
}

void GameView::stop()
{
    timer.stop();
    close();
}
