#ifndef HEADER_GENERATEOBJECTS_HPP_INCLUDED
#define HEADER_GENERATEOBJECTS_HPP_INCLUDED

#include <exception>
#include <stdexcept>

#include <SFML/Graphics.hpp>

#include "../matrix/matrix.hpp"
#include "../object/object.hpp"
#include "../tile/tile.hpp"



// Абстрактный генератор карт
class GenerateObjects
{
protected:
    sf::Vector2u mSize;
public:
    GenerateObjects();
    virtual void operator () (const Matrix<Tile>& map, std::vector< Object* >& R);
};


#endif
//*/