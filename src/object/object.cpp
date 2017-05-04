#include "../object/object.hpp"

Object::Object(int objectType,
           const sf::Vector2u& tileFrom,
           const sf::Vector2u& tileTo,
           unsigned state
          ) :
        GameItem   (objectType, sf::Vector2f(0, 0), state),
        mTileFrom  (tileFrom),
        mTileTo    (tileTo)
{
    
};

void Object::calcSpritePosition ( const sf::Vector2u& tileSize, double time, double stepCount) {
    
    sf::Vector2f positionFrom(mTileFrom.y * tileSize.x, mTileFrom.x * tileSize.y);
    sf::Vector2f positionTo(mTileTo.y * tileSize.x, mTileTo.x * tileSize.y);
    sf::Vector2f objectCurentPosition(  positionFrom.x + time / stepCount * (positionTo.x - positionFrom.x),
                                        positionFrom.y + time / stepCount * (positionTo.y - positionFrom.y) );
    setPosition(objectCurentPosition);
}
