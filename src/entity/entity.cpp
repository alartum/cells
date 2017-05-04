#include "entity.hpp"

Entity::Entity(int entityType,
               const sf::Vector2u &latticePosition,
               unsigned state) :
  Object(entityType, latticePosition, state)
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
