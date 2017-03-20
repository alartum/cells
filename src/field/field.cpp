#include "field.hpp"


 // Конструктор W - окно отрисовки, fSize - вектор размера, fCellSize - размер клетки
Field::Field(sf::RenderWindow & W, sf::Vector2u fSize, sf::Color fBackgroundColor) 
    : fSize(fSize), W(W), fBackgroundColor(fBackgroundColor)
{
}

Field::~Field() {
    for (auto iter: fObjects)
        delete iter;
}

    
// Вывести на W состояния клеток, не выполняется для тех клеток, для которых cType == cPrevType (которые не изменили тип)
void Field::draw()
{
    W.clear(fBackgroundColor);
    for (auto & objectIterator : fObjects)
        objectIterator->draw(W);
}
    
// Функция генерации поля, принимает тип генерируемого поля
void Field::generate(FieldGenerator & G)
{
    G.generate(fSize, fObjects);
}

// Функция пересчета состояния поля на один игровой шаг
//int Field::step(StepAlgorithm & S)
//{
//    return S.step(fObjects);
//}
