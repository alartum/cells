#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../object/object.hpp"

class Entity : public Object
{
public:
    enum State {NONE, THINK, NEW_ACTION, CONTINUE};
    Entity(const std::shared_ptr<ModelManager>& modelManagerPtr,
           int entityType = 0,
           const sf::Vector2f& position = sf::Vector2f(0,0),
           unsigned state = 0);
    void setState (State state);
    State getState() const;
private:
    State mState;
};

#endif // ENTITY_HPP
