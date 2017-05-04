#ifndef HEADER_OBJECT_HPP_INCLUDED
#define HEADER_OBJECT_HPP_INCLUDED

#include "../game_item/gameitem.hpp"

class Object : public GameItem
{
private:
    
public:
    // To animation
    sf::Vector2u mTileFrom;
    sf::Vector2u mTileTo;
    
    // To dostep
    sf::Vector2u mFuturePosition;
    
    
    Object(int objectType = 0,
           const sf::Vector2u& animationFrom = sf::Vector2u(0, 0),
           const sf::Vector2u& animationTo = sf::Vector2u(0, 0),
           unsigned state = 0
          );
    
    void calcSpritePosition ( const sf::Vector2u& tileSize, double stepCount, double time);
};

#endif
