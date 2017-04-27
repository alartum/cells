#include "../object/object.hpp"

Object::Object(int objectType,
               const sf::Vector2f &position,
               unsigned state) :
        GameItem(objectType, position, state)
{

}
