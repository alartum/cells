#ifndef MOVINGENTITY_HPP
#define MOVINGENTITY_HPP

#include "../entity/entity.hpp"

class MovingEntity : public Entity
{
private:
    Direction mDirection;
public:
    enum Direction {NONE, UP, RIGHT, DOWN, LEFT};
    MovingEntity(const std::shared_ptr<ModelManager>& modelManagerPtr,
                 int entityType = 0,
                 const sf::Vector2f& position = sf::Vector2f(0,0),
                 unsigned state = 0);
    void setDirection(Direction direction);
    Direction getDirection() const;
};

#endif // MOVINGENTITY_HPP
