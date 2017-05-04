#include "entity.hpp"

Entity::Entity(int entityType,
           const sf::Vector2u& tileFrom,
           const sf::Vector2u& tileTo,
           unsigned state
          ) :
  Object(entityType, tileFrom, tileTo, state)
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
