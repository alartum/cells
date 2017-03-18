#include "gamescene.h"
#include <QRectF>
#include <QPainter>
#include "QTime"
#include <Qt>
#include <QDebug>

GameScene::GameScene(QObject *parent) :
    QGraphicsScene(parent),
    mMap(mMAP_WIDTH, mMAP_HEIGHT, nullptr)
{
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    this->setSceneRect(0, 0, mWIDTH, mHEIGHT);
    for (int y = 0; y < mMAP_HEIGHT; y++){
        for (int x = 0; x < mMAP_WIDTH; x++){
            Qt::GlobalColor brushColor;
            switch (qrand() % 3){
                case 0:
                    brushColor = Qt::red;
                    break;
                case 1:
                    brushColor = Qt::green;
                    break;
                case 2:
                    brushColor = Qt::white;
                    break;
            }
            QBrush brush(brushColor);
            QPen pen = Qt::NoPen;
            QRectF newRect = getRectForTile(x, y);
            QGraphicsRectItem* newTile = addRect(newRect, pen, brush);
            mMap.setElement(x, y, newTile);
        }
    }
}

GameScene::~GameScene()
{
}

QRectF GameScene::getRectForTile(int x, int y) const
{
    //Возвращаем прямоугольник тайла с номером (x, y) в матрице
    return QRectF(x * mTILE_SIZE, y * mTILE_SIZE, mTILE_SIZE, mTILE_SIZE);
}

int GameScene::getTileSize() const
{
    return mTILE_SIZE;
}

int GameScene::getHeight() const
{
    return mHEIGHT;
}

int GameScene::getWidth() const
{
    return mWIDTH;
}

QSize GameScene::getSize() const
{
    return QSize(mWIDTH, mHEIGHT);
}
