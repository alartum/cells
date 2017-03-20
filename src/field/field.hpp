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
    // Массив указателей на объекты с поля
    std::vector< Object* > fObjects;
    // Ширина и высота поля в пикселах
    sf::Vector2u fSize;
    // Ссылка на окно отрисовки
    sf::RenderWindow & W;
    // Цвет фона поля
    sf::Color fBackgroundColor;
    
public:    
    // Конструктор W - окно отрисовки, fSize - вектор размера
    Field(sf::RenderWindow & W, sf::Vector2u fSize, sf::Color fBackgroundColor);
    
    // Деструктор
    ~Field();
    
    // Вывести на W все объекты (вызвать draw(W) для них)
    void draw();
        
    // Функция генерации поля, принимает ссылку на генератор
    void generate(FieldGenerator & G);

    // Функция пересчета состояния поля на один игровой шаг
    // int action(StepAlgorithm & S);   
    
    // Оператор вывода в поток
    friend std::ostream& operator<< (std::ostream& ostr, Field & F) {
        ostr << "Field: (" << F.fSize.x << ", " << F.fSize.y << ")" << std::endl;
        for (auto & iterator: F.fObjects)
            ostr << "      " << (*iterator) << std::endl;
        return ostr;
    }
};

#endif