#include "../object/object.hpp"

Object::Object(const std::shared_ptr<ModelManager> &modelManagerPtr,
               int objectType,
               const sf::Vector2f &position,
               unsigned state) :
        GameItem(modelManagerPtr, objectType, position, state)
{

}
