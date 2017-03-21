#include "object.hpp"
/////////////////////////////////////////////////////////
Object::~Object() {

}

/////////////////////////////////////////////////////////
// GRASS
/////////////////////////////////////////////////////////
Grass::Grass ( sf::Vector2i gLocation, double gRadius ) 
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

bool Grass::isIntersect ( Grass& Other ) {
    int ro2 = (gLocation.x - Other.gLocation.x) * (gLocation.x - Other.gLocation.x);
    ro2 += (gLocation.y - Other.gLocation.y) * (gLocation.y - Other.gLocation.y);
    double r2 = (gRadius) * (gRadius);
    return (ro2 < r2);
}


Grass::~Grass() {

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



