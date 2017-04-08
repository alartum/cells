#include "movingentity.hpp"

MovingEntity::MovingEntity(const std::shared_ptr<ModelManager> &modelManagerPtr,
                           int entityType,
                           const sf::Vector2f &position,
                           unsigned state) :
    Entity(modelManagerPtr, tileType, position, state),
      mDirection(MovingEntity::Direction::NONE)
{

}

void MovingEntity::setDirection(MovingEntity::Direction direction)
{
    mDirection = direction;
}

MovingEntity::Direction MovingEntity::getDirection() const
{
    return mDirection;
}
