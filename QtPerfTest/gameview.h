#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QTimer>
#include "gamescene.h"

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = 0);
    ~GameView();
    void start(int msec = 50);
    void stop();
private:
    GameScene *gameScene;
    QTimer timer;
};

#endif // GAMEVIEW_H
