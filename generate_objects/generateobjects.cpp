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

GenerateRandomEntity::GenerateRandomEntity (double      grasseating_density,
                        unsigned    grasseating_distance,
                        unsigned    grasseating_neightbors_min,
                        unsigned    grasseating_neightbors_max,

                        double      predators_density,
                        unsigned    predators_distance,
                        unsigned    predator_neightbors_min,
                        unsigned    predator_neightbors_max
                      ) :
                grasseating_density_              (grasseating_density),
                grasseating_distance_             (grasseating_distance),
                grasseating_neightbors_min_        (grasseating_neightbors_min),
                grasseating_neightbors_max_        (grasseating_neightbors_max),
                
                predators_density_                (predators_density),
                predators_distance_               (predators_distance),
                predator_neightbors_min_           (predator_neightbors_min),
                predator_neightbors_max_           (predator_neightbors_max)
{};


#include "../generate_map/generatemap.hpp"
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
        grasseating_density_, grasseating_distance_, grasseating_neightbors_min_, grasseating_neightbors_max_,
        predators_density_, predators_distance_, predator_neightbors_min_, predator_neightbors_max_
    );
    
    
    Matrix< int > IDS (map.getHeight(), map.getWidth(), 0);
    for (unsigned i = 0; i < IDS.getHeight(); i++)
        for (unsigned j = 0; j < IDS.getWidth(); j++) {
            IDS.at(i, j) = OBJECT_UNDEFINED_ID;
        }
    
    std::random_device  rd;
    std::mt19937        mtGenerator(rd());
    
    std::uniform_int_distribution< unsigned >   xDistribution(0, IDS.getHeight()-1);
    std::uniform_int_distribution< unsigned >   yDistribution(0, IDS.getWidth()-1);
    
    // Grass-eating
    for (int i = 0; (double)i * grasseating_density_ < IDS.getHeight() * IDS.getWidth(); i++) {
            unsigned xCurrent = xDistribution(mtGenerator);
            unsigned yCurrent = yDistribution(mtGenerator);

            if (map.at(xCurrent, yCurrent).getID() != TILE_GRASS_ID ||
                IDS.at(xCurrent, yCurrent) != OBJECT_UNDEFINED_ID){
                continue;
            }
            unsigned grassNeightbors = 0;
            
            for (int i = -(int)grasseating_distance_ + (int)xCurrent; i <= (int)grasseating_distance_ + (int)xCurrent; i++)
                for (int j = -(int)grasseating_distance_ + (int)yCurrent; j <= (int)grasseating_distance_ + (int)yCurrent; j++) {
                    if (i >= 0 && i < (int)IDS.getHeight() && j >= 0 && j < (int)IDS.getWidth())
                        if (map.at(i, j).getID() == TILE_GRASS_ID)
                            grassNeightbors += 1;
                }
                
            
            if (grassNeightbors >= grasseating_neightbors_min_ && grassNeightbors <= grasseating_neightbors_max_)
                IDS.at(xCurrent, yCurrent) = OBJECT_GRASS_EATING_ID;
    }
    
    // Predators
     for (int i = 0; (double)i * predators_density_ < IDS.getHeight() * IDS.getWidth(); i++) {
            unsigned xCurrent = xDistribution(mtGenerator);
            unsigned yCurrent = yDistribution(mtGenerator);
            
           if (map.at(xCurrent, yCurrent).getID() != TILE_GRASS_ID ||
                IDS.at(xCurrent, yCurrent) != OBJECT_UNDEFINED_ID)
                continue;
                
            
            unsigned grassNeightbors = 0;
            
            for (int i = -(int)predators_distance_ + (int)xCurrent; i <= (int)predators_distance_ + (int)xCurrent; i++)
                for (int j = -(int)predators_distance_ + (int)yCurrent; j <= (int)predators_distance_ + (int)yCurrent; j++) {
                    if (i >= 0 && i < (int)IDS.getHeight() && j >= 0 && j < (int)IDS.getWidth())
                        if (map.at(i, j).getID() == TILE_GRASS_ID)
                            grassNeightbors += 1;
                }
            
            if (grassNeightbors >= predator_neightbors_min_ && grassNeightbors <= predator_neightbors_max_)
                IDS.at(xCurrent, yCurrent) = OBJECT_PREDATOR_ID;
    }
    
    R.clear();
    for( unsigned i = 0; i < IDS.getHeight(); i++)
        for (unsigned j = 0; j < IDS.getWidth(); j++) {
            //LOG("i=%d, j=%d, IDS.height=%d, IDSwidth=%d",
            //    i, j, IDS.getHeight(), IDS.getWidth()
            //);
            int cur = IDS.at(i, j);
            //LOG("ID=%d", cur)
            if (cur == OBJECT_GRASS_EATING_ID)
                R.push_back(Entity(OBJECT_GRASS_EATING_ID, sf::Vector2u(i, j), sf::Vector2u(i, j)));
            if (cur == OBJECT_PREDATOR_ID)
                R.push_back(Entity(OBJECT_PREDATOR_ID, sf::Vector2u(i, j), sf::Vector2u(i, j)));
            //LOG("finish")
        }
    LOG("FinishFull");
}

                

//*/
