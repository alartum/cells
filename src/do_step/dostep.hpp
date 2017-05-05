#ifndef HEADER_DOSTEP_HPP_INCLUDED
#define HEADER_DOSTEP_HPP_INCLUDED

#include <vector>
#include <random>
#include <set>
#include <vector>
#include "../object/object.hpp"
#include "../matrix/matrix.hpp"
#include "../tile/tile.hpp"
#include "../entity/entity.hpp"

class DoStep {
public:
    DoStep();
    void operator () ( Matrix< Tile >& map, std::vector< Entity >& En );
};

class RandomMoving {
private:
    Matrix< int > cache;
    std::vector< int > color;
public:
    RandomMoving();
    void operator () ( Matrix< Tile >& map, std::vector< Entity >& En );
};


#endif
