#include "field.hpp"


 // Конструктор W - окно отрисовки, fSize - вектор размера, fCellSize - размер клетки
Field::Field(sf::RenderWindow & W, sf::Vector2u fSize, unsigned fCellSize) : 
                fMatrix(fSize.x, fSize.y, Cell()), fSize(fSize), W(W), fCellSize(fCellSize)
{
}
    
// Вывести на W состояния клеток, не выполняется для тех клеток, для которых cType == cPrevType (которые не изменили тип)
void Field::draw()
{
    for (unsigned i = 0; i < fSize.y; i++)
        for (unsigned j = 0; j < fSize.x; j++)
            if (fMatrix.at(i, j).getType() != fMatrix.at(i, j).getPrevType()) {
                switch(fMatrix.at(i, j).getType()) {
                    case Cell::Live:
                        setCellColor(i, j, sf::Color::Red);
                        break;
                    default:
                        setCellColor(i, j, sf::Color::White);    
                }
            }
}
    
// Аналог предыдущей, отрисовываются строго все клетки
void Field::draw_forced()
{
    for (unsigned i = 0; i < fSize.y; i++)
        for (unsigned j = 0; j < fSize.x; j++)
            switch(fMatrix.at(i, j).getType()) {
                case Cell::Live:
                    setCellColor(i, j, sf::Color::Red);
                    break;
                default:
                    setCellColor(i, j, sf::Color::White);    
            }
}
    
// Функция генерации поля, принимает тип генерируемого поля
void Field::generate(FieldGenerator & G)
{
    G.generate(fMatrix);
    fSize = sf::Vector2u(fMatrix.getHeight(), fMatrix.getWidth());
}

// Функция пересчета состояния поля на один игровой шаг
int Field::step(StepAlgorithm & S)
{
    return S.step(fMatrix);
}

// Отрисовать на экране клетку с координатами (x, y) цветом cl
void Field::setCellColor(unsigned x, unsigned y, sf::Color cl)
{
    sf::ConvexShape polygon;
    polygon.setPointCount(4);
    polygon.setPoint(0, sf::Vector2f(0, 0));
    polygon.setPoint(1, sf::Vector2f(0, fCellSize));
    polygon.setPoint(2, sf::Vector2f(fCellSize, fCellSize));
    polygon.setPoint(3, sf::Vector2f(fCellSize, 0));
    polygon.setFillColor(cl);
    polygon.setPosition(x * fCellSize, y * fCellSize);
    W.draw(polygon);
}
