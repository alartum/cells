#ifndef GENERATEMAP_HPP
#define GENERATEMAP_HPP

#include "../matrix/matrix.hpp"
#include "../tile/tile.hpp"
#include "../tileinfo/tileinfo.hpp"


class GenerateMap
{
public:
    GenerateMap();
    // Generate field
    virtual void operator () (Matrix<Tile>& map, TileInfo& info);
};

class GenerateSampleTiles : public GenerateMap
{
public:
    GenerateSampleTiles();
    void operator ()(Matrix<Tile>& map, TileInfo& info);
};

#endif // GENERATEMAP_HPP
