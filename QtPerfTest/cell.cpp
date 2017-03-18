#include "cell.h"

Cell::Cell(QColor color, QGraphicsItem * parent):
QGraphicsRectItem(parent),
mColor(color)
{

}
QColor Cell::getColor() const
{
    return mColor;
}

void Cell::setColor(const QColor &value)
{
    mColor = value;
}

