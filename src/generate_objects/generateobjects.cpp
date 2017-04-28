#include "generateobjects.hpp"

#include <random>
#include <set>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <vector>
#include <random>
#include <ctime>

#define DEBUG
#include "../debug.h"

////////////////////////////////////////////////////////////////////////////////////////////////

GenerateObjects::GenerateObjects()
{
}

void GenerateObjects::operator () (Matrix<Tile>& map, std::vector< Entity > & R)
{
}

GenerateRandomEntity::GenerateRandomEntity (       
                        double      grassEatingDensity,
                        unsigned    grassEatingDistance,
                        unsigned    grassEatingNeightborsMin,
                        unsigned    grassEatingNeightborsMax,
    
                        double      predatorsDensity,
                        unsigned    predatorsDistance,
                        unsigned    predatorNeightborsMin,
                        unsigned    predatorNeightborsMax
                      ) :
                grassEatingDensity              (grassEatingDensity),
                grassEatingDistance             (grassEatingDistance),
                grassEatingNeightborsMin        (grassEatingNeightborsMin),
                grassEatingNeightborsMax        (grassEatingNeightborsMax),
                
                predatorsDensity                (predatorsDensity),
                predatorsDistance               (predatorsDistance),
                predatorNeightborsMin           (predatorNeightborsMin),
                predatorNeightborsMax           (predatorNeightborsMax)
{};

void GenerateRandomEntity::operator() (Matrix< Tile >& map, std::vector< Entity >& R ) {
    LOG("GenerateRandomEntity:\n"
        "               size = (%u, %u)\n"
        "               grassEatingDensity = %lg\n"
        "               grassEatingDistance = %u\n"
        "               grassEatingNeightborsMin = %u\n"
        "               grassEatingNeightborsMax = %u\n"
        "               -------------------------\n"
        "               predatorsDensity = %lg\n"
        "               predatorsDistance = %u\n"
        "               predatorNeightborsMin = %u\n"
        "               predatorNeightborsMax = %u\n",
        map.getHeight(), map.getWidth(),
        grassEatingDensity, grassEatingDistance, grassEatingNeightborsMin, grassEatingNeightborsMax,
        predatorsDensity, predatorsDistance, predatorNeightborsMin, predatorNeightborsMax
    );
    
    
    Matrix< int > IDS (map.getHeight(), map.getWidth(), 0);
    for (unsigned i = 0; i < IDS.getHeight(); i++)
        for (unsigned j = 0; j < IDS.getWidth(); j++) {
            IDS.at(i, j) = map.at(i, j).getTypeID();
        }
    
    std::random_device  rd;
    std::mt19937        mtGenerator(rd());
    
    std::uniform_int_distribution< unsigned >   xDistribution(0, IDS.getHeight());
    std::uniform_int_distribution< unsigned >   yDistribution(0, IDS.getWidth());
    
    // Grass-eating
    for (int i = 0; (double)i * grassEatingDensity < IDS.getHeight() * IDS.getWidth(); i++) {
            unsigned xCurrent = xDistribution(mtGenerator);
            unsigned yCurrent = yDistribution(mtGenerator);
            
            if (IDS.at(xCurrent, yCurrent) != TILE_UNDEFINED_ID &&
                IDS.at(xCurrent, yCurrent) != TILE_GRASS_ID)
                continue;
                
            
            unsigned grassNeightbors = 0;
            
            for (int i = -(int)grassEatingDistance + (int)xCurrent; i <= (int)grassEatingDistance + (int)xCurrent; i++)
                for (int j = -(int)grassEatingDistance + (int)yCurrent; j <= (int)grassEatingDistance + (int)yCurrent; j++) {
                    if (i >= 0 && i < (int)IDS.getHeight() && j >= 0 && j < (int)IDS.getWidth())
                        if (IDS.at(i, j) == TILE_GRASS_ID)
                            grassNeightbors += 1;
                }
            
            if (grassNeightbors >= grassEatingNeightborsMin && grassNeightbors <= grassEatingNeightborsMax)
                IDS.at(xCurrent, yCurrent) = OBJECT_GRASS_EATING_ID;
    }
    
    // Predators
     for (int i = 0; (double)i * predatorsDensity < IDS.getHeight() * IDS.getWidth(); i++) {
            unsigned xCurrent = xDistribution(mtGenerator);
            unsigned yCurrent = yDistribution(mtGenerator);
            
            if (IDS.at(xCurrent, yCurrent) != TILE_UNDEFINED_ID &&
                IDS.at(xCurrent, yCurrent) != TILE_WATER_ID)
                continue;
                
            
            unsigned grassNeightbors = 0;
            
            for (int i = -(int)predatorsDistance + (int)xCurrent; i <= (int)predatorsDistance + (int)xCurrent; i++)
                for (int j = -(int)predatorsDistance + (int)yCurrent; j <= (int)predatorsDistance + (int)yCurrent; j++) {
                    if (i >= 0 && i < (int)IDS.getHeight() && j >= 0 && j < (int)IDS.getWidth())
                        if (IDS.at(i, j) != TILE_WATER_ID && IDS.at(i, j) != TILE_UNDEFINED_ID)
                            grassNeightbors += 1;
                }
            
            if (grassNeightbors >= predatorNeightborsMin && grassNeightbors <= predatorNeightborsMax)
                IDS.at(xCurrent, yCurrent) = OBJECT_PREDATOR_ID;
    }
    
    R.clear();
    for( unsigned i = 0; i < IDS.getHeight(); i++)
        for (unsigned j = 0; j < IDS.getWidth(); j++) {
            int cur = IDS.at(i, j);
            if (IS_GRASS_EATING(cur))
                R.push_back(Entity(OBJECT_GRASS_EATING_ID, sf::Vector2f(i, j)));
            if (IS_PREDATOR(cur))
                R.push_back(Entity(OBJECT_PREDATOR_ID, sf::Vector2f(i, j)));
        }
}

                

//*/
