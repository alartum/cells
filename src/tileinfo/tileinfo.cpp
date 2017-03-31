#include "tileinfo.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/String.hpp>

TileInfo::TileInfo(const sf::Vector2u &tileSize) :
    mTileSize(tileSize)
{

}

sf::Texture& TileInfo::getTexture(Tile::Type type)
{
    return mTextures[type];
}

void TileInfo::addTexture(Tile::Type type, const sf::Texture& texture)
{
    mTextures.insert(std::pair<Tile::Type, sf::Texture>(type, texture));
}

sf::Vector2u TileInfo::getTileSize()
{
    return mTileSize;
}
