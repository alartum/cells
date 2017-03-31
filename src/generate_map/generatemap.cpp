#include "generatemap.hpp"

GenerateMap::GenerateMap()
{

}

void GenerateMap::operator () (Matrix<Tile>& map, TileInfo &info)
{
}

GenerateSampleTiles::GenerateSampleTiles()
{
}

void GenerateSampleTiles::operator ()(Matrix<Tile>& map, TileInfo &info)
{
    for (unsigned x = 0; x < map.getWidth(); x++){
        for (unsigned y = 0; y < map.getWidth(); y++){
            Tile& current = map.at(x, y);
            current.setType(Tile::Water);
            Tile::Type type = current.getType();
            sf::Texture& texture = info.getTexture(type);
            sf::Sprite& sprite = current.getSprite();
            sprite.setTexture(texture);
            float xpos = x*info.getTileSize().x;
            float ypos = y*info.getTileSize().y;
            sprite.setPosition(xpos, ypos);
            current.setUpdated(true);
        }
    }
}
