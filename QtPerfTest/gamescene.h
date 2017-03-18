#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include "matrix.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
     explicit GameScene(QObject *parent = 0);
    ~GameScene();
    int getTileSize() const;
    int getHeight() const;
    int getWidth() const;
    QSize getSize() const;
private:
    // In tiles
    const int mMAP_HEIGHT = 200;
    const int mMAP_WIDTH = 200;
    // In pixels
    const int mTILE_SIZE = 3;
    const int mHEIGHT = mMAP_HEIGHT * mTILE_SIZE;
    const int mWIDTH = mMAP_WIDTH * mTILE_SIZE;
    Matrix<QGraphicsRectItem*> mMap;

    QRectF getRectForTile(int x, int y) const;
};

#endif // GAMESCENE_H
