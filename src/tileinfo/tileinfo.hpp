#ifndef TILEINFO_HPP
#define TILEINFO_HPP

#include "../tile/tile.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <map>

class TileInfo
{
public:
    TileInfo(const sf::Vector2u& tileSize = sf::Vector2u(34, 34));
    sf::Texture& getTexture(Tile::Type type);
    void addTexture(Tile::Type type, const sf::Texture& texture);
    sf::Vector2u getTileSize();
private:
    std::map<Tile::Type, sf::Texture> mTextures;
    sf::Vector2u mTileSize;
};

#endif // TILEINFO_HPP
