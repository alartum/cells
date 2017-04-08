#ifndef HEADER_TILE_HPP_INCLUDED
#define HEADER_TILE_HPP_INCLUDED

#include "../game_item/gameitem.hpp"
#include "../object/object.hpp"
#include <list>

class Tile : public GameItem
{
public:
    Tile(const std::shared_ptr<ModelManager>& modelManagerPtr,
         int tileType = 0,
         const sf::Vector2f& position = sf::Vector2f(0,0),
         unsigned state = 0);
    // Objects in current tile
    // May be used to optimise interacting
    std::list<std::shared_ptr<Object> > mObjects;
};

#endif
