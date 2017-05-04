#ifndef HEADER_OBJECT_HPP_INCLUDED
#define HEADER_OBJECT_HPP_INCLUDED

#include "../game_item/gameitem.hpp"

class Object : public GameItem
{
public:
    Object(int objectType = 0,
           const sf::Vector2u& latticePosition = sf::Vector2u(0,0),
           unsigned state = 0);
};

#endif
