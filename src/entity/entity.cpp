#include "entity.hpp"

Entity::Entity(const std::shared_ptr<ModelManager> &modelManagerPtr,
               int entityType,
               const sf::Vector2f &position,
               unsigned state) :
Object(modelManagerPtr, tileType, position, state),
  mState(Entity::State::NONE)
{

}

void Entity::setState (Entity::State state)
{
    mState = state;
}

Entity::State Entity::getState() const
{
    return mState;
}
