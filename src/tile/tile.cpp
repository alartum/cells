#include "tile.hpp"

Tile::Tile(int tileType,
            const sf::Vector2u &latticePosition,
            unsigned state
          ) :
    GameItem(tileType, latticePosition, state)
{
}

Tile::Tile ( const Tile& other ) : 
    GameItem (other.mTypeID, other.getLatticePosition(), other.mState) {
    setModelManager(other.getModelManager());
}

Tile::Tile ( Tile&& other ) : 
    GameItem (other.mTypeID, other.getLatticePosition(), other.mState) {
    setModelManager(other.getModelManager());
}

 Tile& Tile::operator = (const Tile& other){
     GameItem:: operator = (other);
     return *this;
 }
