#include "entity.hpp"

Entity::Entity(int entityType,
               const sf::Vector2f &position,
               unsigned state) :
  Object(entityType, position, state)
{

}

/*void Entity::setState (Entity::State state)
{
    mState = state;
}

Entity::State Entity::getState() const
{
    return mState;
}
*/
