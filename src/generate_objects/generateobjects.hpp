#include <exception>
#include <stdexcept>

#include <SFML/Graphics.hpp>

#include "../matrix/matrix.hpp"
#include "../object/object.hpp"
#include "../tile/tile.hpp"


#ifndef HEADER_GENERATEOBJECTS_HPP_INCLUDED
#define HEADER_GENERATEOBJECTS_HPP_INCLUDED

// Абстрактный генератор карт
class GenerateObjects
{
protected:
    sf::Vector2u mSize;
public:
    GenerateObjects();
    // Генерация поля
    virtual void operator () (const Matrix<Tile>& map, std::vector< Object* >& R);
};

// Генератор некоего ландшафта
class LandscapeGenerator : public GenerateObjects
{
private:
    int grassCount;
    double grassRadius;
public:
    LandscapeGenerator(int grassCount, double grassRadius);
    // Генерация поля на матрице R
    void operator () (const Matrix<Tile>& map, std::vector< Object* > & R);
};

#endif
