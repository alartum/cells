#ifndef HEADER_FIELD_HPP_INCLUDED
#define HEADER_FIELD_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "../matrix/matrix.hpp"
#include "../object/object.hpp"
#include "../generator/generator.hpp"
#include "../step_algorithm/step_algorithm.hpp"

class Field 
{
private:
    // Матрица клеток
    std::vector< Object > fObjects;
    // Ширина и высота поля в пикселах
    sf::Vector2u fSize;
    // Ссылка на окно отрисовки
    sf::RenderWindow & W;
    
public:    
    // Конструктор W - окно отрисовки, fSize - вектор размера
    Field(sf::RenderWindow & W, sf::Vector2u fSize);
    
    // Вывести на W все объекты (вызвать draw(W) для них)
    void draw();
        
    // Функция генерации поля, принимает ссылку на генератор
    void generate(FieldGenerator & G);

    // Функция пересчета состояния поля на один игровой шаг
    int action(StepAlgorithm & S);   
};

#endif