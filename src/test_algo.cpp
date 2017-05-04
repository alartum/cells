#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>

#include "tile/tile.hpp"
#include "matrix/matrix.hpp"
#include "entity/entity.hpp"
#include "field/field.hpp"


#include "generate_map/generatemap.hpp"
#include "generate_objects/generateobjects.hpp"

#include "debug.h"



int test_algo(int argc, char** argv, char** env) {
    sf::Vector2u fieldSize(20, 20);
    sf::Vector2u tileSize(32, 32);
    sf::Vector2u windowSize(640, 860);

    Field F(fieldSize, windowSize, tileSize);
    Matrix< Tile >              map(fieldSize.x, fieldSize.y);
    std::vector< Entity >       ent;
        
    GenerateRandomMap mapGenerator(8, 0.01, 0.2, 15);
    F.generateTiles(mapGenerator);
    
    GenerateRandomEntity entityGenerator(1, 3, 0, 30, 1, 3, 0, 3);
    F.generateEntities(entityGenerator);
    
    MapDump MD;
    
    MD(F.mMap, F.mEntities);
    
    return 0;
}

