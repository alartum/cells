#ifndef HEADER_TILE_HPP_INCLUDED
#define HEADER_TILE_HPP_INCLUDED

#include "../game_item/gameitem.hpp"
#include "../object/object.hpp"
#include <list>

class Tile : public GameItem
{
public:
    Tile(int tileType = 0,
         const sf::Vector2f& position = sf::Vector2f(0,0),
         unsigned state = 0);
    Tile(const Tile& other);
    Tile(Tile&& other);
    
     Tile& operator = (const Tile& other);
};

#endif
