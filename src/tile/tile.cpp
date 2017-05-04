#include "tile.hpp"

Tile::Tile(int tileType,
            const sf::Vector2f &position,
            unsigned state
          ) :
    GameItem(tileType, position, state)
{
}

Tile::Tile ( const Tile& other ) : 
    GameItem (other.mTypeID, other.getPosition(), other.mState) {
    setModelManager(other.getModelManager());
}

Tile::Tile ( Tile&& other ) : 
    GameItem (other.mTypeID, other.getPosition(), other.mState) {
    setModelManager(other.getModelManager());
}

 Tile& Tile::operator = (const Tile& other){
     GameItem:: operator = (other);
     return *this;
 }
