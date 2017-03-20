#ifndef HEADER_OBJECT_HPP_INCLUDED
#define HEADER_OBJECT_HPP_INCLUDED
#include <SFML/Graphics/RenderWindow.hpp>


class Object 
{
public:
    enum object_type_t {Water, Grass};
    
protected:
    object_type_t oType;
    
    
public:
    Object();
    void draw(sf::RenderWindow & W) = 0;
    
    object_type_t getType() const;
};


class Grass : public Object
{
protected:
    sf::Vector2u gLocation;
public:
    Grass();
    Grass(sf::Vector2u gLocation);
    
    void draw(sf::RenderWindow & W);
};

#endif