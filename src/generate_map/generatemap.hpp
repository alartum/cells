#ifndef GENERATEMAP_HPP
#define GENERATEMAP_HPP

#include "../matrix/matrix.hpp"
#include "../tile/tile.hpp"


class GenerateMap
{
public:
    GenerateMap();
    // Generate field
    virtual void operator () (Matrix<Tile>& map);
};

class GenerateSampleTiles : public GenerateMap
{
public:
    GenerateSampleTiles();
    void operator ()(Matrix<Tile>& map);
};

#endif // GENERATEMAP_HPP
