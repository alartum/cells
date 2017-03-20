#include "object.hpp"

Object::object_type_t Object::getType() const {
    return oType;
}
/////////////////////////////////////////////////////////

Grass::Grass() : Object() {
    oType = Object::Grass;
}

Grass::Grass ( sf::Vector2u gLocation ) : Object(), gLocation(gLocation) {
    oType = Object::Grass;
}


