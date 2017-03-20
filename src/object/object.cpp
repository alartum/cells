#include "object.hpp"

/////////////////////////////////////////////////////////
// GRASS
/////////////////////////////////////////////////////////
Grass::Grass ( sf::Vector2u gLocation, double gRadius ) 
                : Object(), gLocation(gLocation), gRadius(gRadius) {
    oType = Object::Grass;
}

Grass::Grass ( Grass& Other ) : Object() {
    gLocation = Other.gLocation;
    gRadius = Other.gRadius;
}

Grass::Grass ( Grass&& Other ) : Object() {
    gLocation = Other.gLocation;
    gRadius = Other.gRadius;
}

void Grass::draw ( sf::RenderWindow& W ) {
    sf::CircleShape CH(gRadius, 30);
    CH.setPosition(gLocation.x, gLocation.y);
    CH.setFillColor(sf::Color::Green);
    W.draw(CH);
}

Grass& Grass::operator= ( const Grass& Other ) {
    gLocation = Other.gLocation;
    gRadius  = Other.gRadius;
    return *this;
}

Grass& Grass::operator= ( const Grass&& Other ) {
    gLocation = Other.gLocation;
    gRadius  = Other.gRadius;
    return *this;
}



