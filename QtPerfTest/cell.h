#ifndef CELL_H
#define CELL_H

#include <QGraphicsRectItem>
#include <QColor>

class Cell : public QGraphicsRectItem
{
public:
    Cell(QColor color = Qt::white, QGraphicsItem * parent = 0);
    QColor getColor() const;
    void setColor(const QColor &value);
private:
    QColor mColor;
};

#endif // CELL_H
