#ifndef HEADER_FIELD_HPP_INCLUDED
#define HEADER_FIELD_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "../matrix/matrix.hpp"
#include "../cell/cell.hpp"
#include "generator.hpp"
#include "step_algorithm.hpp"

class Field 
{
private:
    // Матрица клеток
    Matrix< Cell > fMatrix;
    // Ширина и высота поля в клетках
    sf::Vector2u fSize;
    // Ссылка на окно отрисовки
    sf::RenderWindow & W;
    // Размер клетки (в пикселях)
    unsigned fCellSize = 0;
    
    // Отрисовать на экране клетку с координатами (x, y) цветом cl
    void setCellColor(unsigned x, unsigned y, sf::Color cl);
    
public:    
    // Конструктор W - окно отрисовки, fSize - вектор размера, fCellSize - размер клетки
    Field(sf::RenderWindow & W, sf::Vector2u fSize, unsigned fCellSize);
    
    // Вывести на W состояния клеток, не выполняется для тех клеток, для которых cType == cPrevType (которые не изменили тип)
    void draw();
    
    // Аналог предыдущей, отрисовываются строго все клетки
    void draw_forced();
    
    // Функция генерации поля, принимает ссылку на генератор
    void generate(FieldGenerator & G);

    // Функция пересчета состояния поля на один игровой шаг
    int step(StepAlgorithm & S);   
};

#endif