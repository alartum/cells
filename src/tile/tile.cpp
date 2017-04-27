#include "tile.hpp"

Tile::Tile(const std::shared_ptr<const ModelManager>& modelManagerPtr,
            int tileType,
            const sf::Vector2f &position,
            unsigned state
          ) :
    GameItem(modelManagerPtr, tileType, position, state)
{
}

Tile::Tile ( const Tile& other ) : 
    GameItem (other.mModelManager, other.mTypeID, other.getPosition(), other.mState) {

}

Tile::Tile ( Tile&& other ) : 
    GameItem (other.mModelManager, other.mTypeID, other.getPosition(), other.mState) {

}


