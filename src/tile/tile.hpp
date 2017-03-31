#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#ifndef HEADER_TILE_HPP_INCLUDED
#define HEADER_TILE_HPP_INCLUDED

class Tile
{
public:
    enum Type {Clear = 0,
               Live  = 1,
               Water = 2,
               Green = 3};
    
private:
    Type mType;
    sf::Sprite mSprite;
    bool mIsUpdated;
public:
    Tile();
    Tile(Type type, const sf::Texture& texture);
    Tile::Type getType() const;
    void setType(Type type);
    sf::Sprite& getSprite();
    void setSprite(const sf::Texture& texture);
    bool isUpdated() const;
    void setUpdated(bool isUpdated);
};

#endif
