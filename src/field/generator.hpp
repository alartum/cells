#ifndef HEADER_GENERATOR_HPP_INCLUDED
#define HEADER_GENERATOR_HPP_INCLUDED

#include <exception>
#include <stdexcept>

#include <SFML/Graphics.hpp>

#include "../matrix/matrix.hpp"
#include "../cell/cell.hpp"

// Абстрактный генератор карт, предствлен в виде функтора
class FieldGenerator
{
protected:
    sf::Vector2u fSize;
public:
    FieldGenerator(sf::Vector2u fSize);
    // Генерация поля
    virtual void generate (Matrix< Cell> & R) = 0;
};

// Генератор поля, на котором клетки имеют тип Live с вероятностью probability
class UniformRandomFieldGenerator : public FieldGenerator
{
private:
    double probability;
public:
    UniformRandomFieldGenerator(sf::Vector2u fSize, double probability);
    // Генерация поля на матрице R
    void generate (Matrix< Cell> & R);
};

#endif