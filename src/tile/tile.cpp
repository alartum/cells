#include "tile.hpp"

Tile::Tile() :
    mIsUpdated(false)
{
}

Tile::Tile(Tile::Type type, const sf::Texture &texture) :
    mType(type),
    mSprite(texture),
    mIsUpdated(true)
{
}

Tile::Type Tile::getType() const
{
    return mType;
}

void Tile::setType(Tile::Type type)
{
    mType = type;
}

sf::Sprite& Tile::getSprite()
{
    return mSprite;
}

void Tile::setSprite(const sf::Texture& texture)
{
    mSprite.setTexture(texture);
}

bool Tile::isUpdated() const
{
    return mIsUpdated;
}

void Tile::setUpdated(bool isUpdated)
{
    mIsUpdated = isUpdated;
}
