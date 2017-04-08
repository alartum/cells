#include "tile.hpp"

Tile::Tile(const std::shared_ptr<ModelManager> &modelManagerPtr,
           int tileType,
           const sf::Vector2f &position,
           unsigned state) :
    GameItem(modelManagerPtr, tileType, position, state)
{
}
