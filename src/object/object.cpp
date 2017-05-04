#include "../object/object.hpp"

Object::Object(int objectType,
               const sf::Vector2u &latticePosition,
               unsigned state) :
        GameItem(objectType, latticePosition, state)
{

}
