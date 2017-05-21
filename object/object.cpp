#include "../object/object.hpp"
#define DEBUG
#include "../debug.h"

Object::Object ( int objectType,
                 const sf::Vector2u& tileFrom,
                 const sf::Vector2u& tileTo,
                 unsigned state
               ) :
    GameItem ( objectType, sf::Vector2f ( 0, 0 ), state ),
    tile_from_ ( tileFrom ),
    tile_to_ ( tileTo ) {

};

Object& Object:: operator = (Object& other) {
    tile_from_ = other.tile_from_;
    tile_to_ = other.tile_to_;
    future_position_ = other.future_position_;
    
    /*mModelManager = other.mModelManager;
    setTypeID(other.mTypeID);
    
    mModel = other.mModel;
    mFrameNo = other.mFrameNo;
    mAnimation = other.mAnimation;
    mFramesAmount = other.mFramesAmount;
    mState = other.mState;
    */
    return (*this);
}

void Object::calcSpritePosition ( const sf::Vector2u& tileSize, double time, double stepCount ) {

    sf::Vector2f positionFrom ( tile_from_.y * tileSize.x, tile_from_.x * tileSize.y );
    sf::Vector2f positionTo ( tile_to_.y * tileSize.x, tile_to_.x * tileSize.y );
    sf::Vector2f objectCurentPosition ( positionFrom.x + time / stepCount * ( positionTo.x - positionFrom.x ),
                                        positionFrom.y + time / stepCount * ( positionTo.y - positionFrom.y ) );
    setPosition ( objectCurentPosition );
}

const sf::Vector2u& Object::getTileFrom() const {
    return tile_from_;
}

const sf::Vector2u& Object::getTileTo() const {
    return tile_to_;
}

void Object::setTileFrom(const sf::Vector2u& tile_from){
    tile_from_ = tile_from;
}

void Object::setTileTo(const sf::Vector2u& tile_to){
    tile_to_ = tile_to;
}

const sf::Vector2u& Object::getFuturePosition() const{
    return future_position_;
}

void Object::setFuturePosition(const sf::Vector2u& future_position){
    future_position_ = future_position;
}

void Object::updateRoute(){
    tile_from_ = tile_to_;
    tile_to_ = future_position_;
    sf::Vector2i direction((int)tile_to_.x - (int)tile_from_.x,
                           (int)tile_to_.y - (int)tile_from_.y);
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
