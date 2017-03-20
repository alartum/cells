#ifndef HEADER_GENERATOR_HPP_INCLUDED
#define HEADER_GENERATOR_HPP_INCLUDED

#include <exception>
#include <stdexcept>

#include <SFML/Graphics.hpp>

#include "../object/object.hpp"
#include "../field/field.hpp"

// Абстрактный генератор карт
class FieldGenerator
{
protected:
    sf::Vector2u fSize;
public:
    FieldGenerator(sf::Vector2u fSize);
    // Генерация поля
    virtual void generate (std::vector< Object > & R) = 0;
};

// Генератор некоего ландшафта
class LandscapeGenerator : public FieldGenerator
{
private:
    double waterRadius;
    int waterCount;
public:
    LandscapeGenerator(sf::Vector2u fSize, int waterCount, double waterRadius);
    // Генерация поля на матрице R
    void generate (std::vector< Object > & R);
};

#endif