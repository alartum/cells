#ifndef HEADER_OBJECT_HPP_INCLUDED
#define HEADER_OBJECT_HPP_INCLUDED

#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string>
#include <iterator>

#include "../game_item/gameitem.hpp"

class Object : public GameItem {
private:
    // To animation
    sf::Vector2u tile_from_;
    sf::Vector2u tile_to_;
    // To dostep
    sf::Vector2u future_position_;
public:
    Object ( int objectType = 0,
             const sf::Vector2u& animationFrom = sf::Vector2u ( 0, 0 ),
             const sf::Vector2u& animationTo = sf::Vector2u ( 0, 0 ),
             unsigned state = 0
           );
    std::map< std::string, int > properties;
    
    Object& operator = (Object& other);
    
    const sf::Vector2u& getTileFrom()    const;
    const sf::Vector2u& getTileTo()      const;
    void calcSpritePosition ( const sf::Vector2u& tileSize, double stepCount, double time );
    void setTileFrom(const sf::Vector2u& tile_from);
    // Use after set tile from to get appropriate results
    void setTileTo(const sf::Vector2u& tile_to);
    const sf::Vector2u& getFuturePosition() const;
    void setFuturePosition(const sf::Vector2u& future_position);
    // TileFrom is replaced with TileTo
    // TileTo is replaced with future position
    void updateRoute();
};

#endif
