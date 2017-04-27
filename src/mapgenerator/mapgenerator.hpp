#ifndef MAPGENERATOR_HPP
#define MAPGENERATOR_HPP

#include "../matrix/matrix.hpp"
#include "../tile/tile.hpp"


class MapGenerator
{
public:
    MapGenerator();
    virtual void operator () (Matrix<Tile>& map) = 0;
};

#endif // MAPGENERATOR_HPP
