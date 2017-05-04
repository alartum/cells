#ifndef HEADER_TILE_HPP_INCLUDED
#define HEADER_TILE_HPP_INCLUDED

#include "../game_item/gameitem.hpp"
#include "../object/object.hpp"
#include <list>

class Tile : public GameItem
{
public:
    Tile(int tileType = 0,
         const sf::Vector2u& latticePosition = sf::Vector2u(0,0),
         unsigned state = 0);
    Tile(const Tile& other);
    Tile(Tile&& other);
    
    // Objects in current tile
    // May be used to optimise interacting
     std::list<std::shared_ptr<Object> > mObjects;
     Tile& operator = (const Tile& other);
};

#endif
