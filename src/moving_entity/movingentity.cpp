#include "movingentity.hpp"

MovingEntity::MovingEntity(int entityType,
                           const sf::Vector2f &position,
                           unsigned state) :
    Entity(entityType, position, state),
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
