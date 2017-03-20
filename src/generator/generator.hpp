#ifndef HEADER_GENERATOR_HPP_INCLUDED
#define HEADER_GENERATOR_HPP_INCLUDED

#include <exception>
#include <stdexcept>

#include <SFML/Graphics.hpp>

#include "../object/object.hpp"

// Абстрактный генератор карт
class FieldGenerator
{
protected:
    sf::Vector2u fSize;
public:
    FieldGenerator();
    // Генерация поля
    virtual void generate (sf::Vector2u fSize, std::vector< Object* > & R) = 0;
};

// Генератор некоего ландшафта
class LandscapeGenerator : public FieldGenerator
{
private:
    int grassCount;
    double grassRadius;
public:
    LandscapeGenerator(int grassCount, double grassRadius);
    // Генерация поля на матрице R
    void generate (sf::Vector2u fSize, std::vector< Object* > & R);
};

#endif