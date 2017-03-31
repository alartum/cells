#include "generateobjects.hpp"

#include <random>
#include <set>
#include <ctime>
#include <cstdlib>

////////////////////////////////////////////////////////////////////////////////////////////////

GenerateObjects::GenerateObjects()
{
}

void GenerateObjects::operator () (const Matrix<Tile>& map, std::vector< Object* > & R)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
LandscapeGenerator::LandscapeGenerator ( int grassCount, double grassRadius ) 
    : grassCount(grassCount), grassRadius(grassRadius) {
}

void LandscapeGenerator::operator ()(const Matrix<Tile>& map, std::vector< Object* >& R ) {
    sf::Vector2u fSize(map.getWidth(), map.getHeight());
    std::normal_distribution< double > xDistribution((double)fSize.x / 2, (double)fSize.x / 2);
    std::normal_distribution< double > yDistribution((double)fSize.y / 2, (double)fSize.x / 2);
    std::normal_distribution< double > rDistribution(grassRadius, grassRadius / 2);
    std::random_device rd; //
    std::mt19937 generator(rd());
    
    R.clear();
    for (int i = 0; i < grassCount; i++) {
        int x = -1;
        while (x >= (int)fSize.x || x < 0)
            x = static_cast< int >(xDistribution(generator));
        int y = -1;
        while (y >= (int)fSize.y || y < 0)
            y = static_cast< int >(yDistribution(generator));
        double r = rDistribution(generator);
        
        Grass* G = new Grass(sf::Vector2i(x, y), r);
        R.push_back(G);
    }
}
