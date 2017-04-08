#ifndef HEADER_OBJECT_HPP_INCLUDED
#define HEADER_OBJECT_HPP_INCLUDED

#include "../game_item/gameitem.hpp"

class Object : public GameItem
{
public:
    Object(const std::shared_ptr<ModelManager>& modelManagerPtr,
           int objectType = 0,
           const sf::Vector2f& position = sf::Vector2f(0,0),
           unsigned state = 0);
};

#endif
