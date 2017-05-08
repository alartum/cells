#include "../object/object.hpp"
#define DEBUG
#include "debug.h"

Object::Object ( int objectType,
                 const sf::Vector2u& tileFrom,
                 const sf::Vector2u& tileTo,
                 unsigned state
               ) :
    GameItem ( objectType, sf::Vector2f ( 0, 0 ), state ),
    mTileFrom ( tileFrom ),
    mTileTo ( tileTo ) {

};

void Object::calcSpritePosition ( const sf::Vector2u& tileSize, double time, double stepCount ) {

    sf::Vector2f positionFrom ( mTileFrom.y * tileSize.x, mTileFrom.x * tileSize.y );
    sf::Vector2f positionTo ( mTileTo.y * tileSize.x, mTileTo.x * tileSize.y );
    sf::Vector2f objectCurentPosition ( positionFrom.x + time / stepCount * ( positionTo.x - positionFrom.x ),
                                        positionFrom.y + time / stepCount * ( positionTo.y - positionFrom.y ) );
    setPosition ( objectCurentPosition );
}

const sf::Vector2u& Object::getTileFrom() const {
    return mTileFrom;
}

const sf::Vector2u& Object::getTileTo() const {
    return mTileTo;
}

void Object::setTileFrom(const sf::Vector2u& tile_from){
    mTileFrom = tile_from;
}

void Object::setTileTo(const sf::Vector2u& tile_to){
    mTileTo = tile_to;
}

const sf::Vector2u& Object::getFuturePosition() const{
    return mFuturePosition;
}

void Object::setFuturePosition(const sf::Vector2u& future_position){
    mFuturePosition = future_position;
}

void Object::updateRoute(){
    mTileFrom = mTileTo;
    mTileTo = mFuturePosition;
    sf::Vector2i direction((int)mTileTo.x - (int)mTileFrom.x,
                           (int)mTileTo.y - (int)mTileFrom.y);
    int dir;
    // Don't ask me about this numbers
    // Coordinates of matrix + Coordinates of field
    // = Creepy as hell
    if (direction.y == 1){
        dir = DIR_RIGHT;
    }
    else if (direction.y == -1){
        dir = DIR_LEFT;
    }
    else if (direction.x == -1){
        dir = DIR_UP;
    }
    else if (direction.x == 1){
        dir = DIR_DOWN;
    }
    else if (direction.x == 0 && direction.y == 0){
        setState(STATE_IDLE | DIR_MASK(getState()));
        return;
    }
    else{
        return;
    }
    setState(STATE_WALK | dir);
}
