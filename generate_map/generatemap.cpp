#include "generatemap.hpp"
#include <random>
#include <numeric>
#include <iterator>
#include <algorithm>

#define DEBUG
#include "../debug.h"

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

GenerateMap::GenerateMap() {
	std::random_device  tempRandomDevice;
    mtGenerator = std::minstd_rand(tempRandomDevice());
}

void GenerateMap::operator() ( Matrix< Tile >& map ) {

}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

#define TEST_WATER(y, x) (map.at(y, x).getID() & TILE_WATER_ID)
int GenerateMap::getEdgeType(Matrix< Tile >& map, unsigned y, unsigned x){
    int edgeType = 0;
    unsigned maxX = map.getWidth() -1;
    unsigned maxY = map.getHeight()-1;
    if (y != 0 && TEST_WATER(y-1, x)) edgeType |= DIR_UP;
    if (y != maxY && TEST_WATER(y+1, x)) edgeType |= DIR_DOWN;
    if (x != 0 && TEST_WATER(y, x-1)) edgeType |= DIR_LEFT;
    if (x != maxX && TEST_WATER(y, x+1)) edgeType |= DIR_RIGHT;\
    if (edgeType == 0){
        if (y != 0 && x != 0 && TEST_WATER(y-1, x-1)) edgeType |= DIR_UP | DIR_LEFT | DIR_ADD;
        if (y != maxY && x != 0 && TEST_WATER(y+1, x-1)) edgeType |= DIR_DOWN | DIR_LEFT | DIR_ADD;
        if (y != 0 && x != maxX && TEST_WATER(y-1, x+1)) edgeType |= DIR_UP | DIR_RIGHT | DIR_ADD;
        if (y != maxY && x != maxX && TEST_WATER(y+1, x+1)) edgeType |= DIR_DOWN | DIR_RIGHT | DIR_ADD;
    }
    if (edgeType == 0)
        return DIR_ADD;
    return edgeType;
}
#undef TEST_WATER

void GenerateMap::fancyEdges(Matrix< Tile >& map ){
    for (unsigned y = 0; y < map.getHeight(); y++)
        for (unsigned x = 0; x < map.getWidth(); x++) {
            Tile& tile = map.at(y, x);
            if (tile.getID() & TILE_GRASS_ID){
                tile.setState(getEdgeType(map, y, x));
            }
        }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////



GenerateRandomMap::GenerateRandomMap (unsigned grassGroupCount, double grassDispersionMin, double grassDispersionMax, double grassDensity ) :
	GenerateMap(), 
    grass_group_count_(grassGroupCount), grass_dispersion_min_(grassDispersionMin), grass_dispersion_max_(grassDispersionMax), grass_density_(grassDensity) 
{
}

void GenerateRandomMap::operator() ( Matrix< Tile >& map ) {

    LOG("RandomMapGenerate:\n"
        "               size = (%u, %u)\n"
        "               grassGroupCount = %u\n"
        "               grassDispersionMin = %lg\n"
        "               grassDispersionMax = %lg\n"
        "               grassDensity = %lg",
        map.getHeight(), map.getWidth(),
        grass_group_count_, grass_dispersion_min_, grass_dispersion_max_, grass_density_);
  
    // Размеры поля
    unsigned mapHeight  = map.getHeight();
    unsigned mapWidth   = map.getWidth();
    
    // Относительное положение центра травы
    std::uniform_real_distribution< double >    grassCentreDistribution(0, 1);
    std::uniform_real_distribution< double >    grassDispersionDistribution(grass_dispersion_min_, grass_dispersion_max_);
    
    for (unsigned i = 0; i < mapHeight; i++)
        for (unsigned j = 0; j < mapWidth; j++)
            map.at(i, j).setID(TILE_WATER_ID);
    
    for (unsigned i = 0; i < grass_group_count_; i++) {
        
        // Координаты текущего центра
        double xCoord = grassCentreDistribution(mtGenerator);
        double yCoord = grassCentreDistribution(mtGenerator);
        
        // Распределения травы вокруг центра
        std::normal_distribution< double > xGrassDistribution(xCoord, grassDispersionDistribution(mtGenerator));
        std::normal_distribution< double > yGrassDistribution(yCoord, grassDispersionDistribution(mtGenerator));
        
        for (unsigned j = 0; (double)j * grass_density_ < (double)(mapHeight * mapWidth); j++) {
            double xCurrent = xGrassDistribution(mtGenerator);
            double yCurrent = yGrassDistribution(mtGenerator);
            
            if (xCurrent >= 1 || xCurrent < 0 || yCurrent >= 1 || yCurrent < 0) // Трава сгенерировалась за пределами карты
                continue;
            
            map.at(
                static_cast< unsigned >(xCurrent * mapHeight), 
                static_cast< unsigned >(yCurrent * mapWidth)
            ).setID(TILE_GRASS_ID);
        }
    }
    GenerateMap::fancyEdges(map);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

GenerateComplexMap::GenerateComplexMap ( unsigned int grassGroupCount, double grassDispersionMin, double grassDispersionMax, double grassDensity ) :
	GenerateMap(), 
    grass_group_count_(grassGroupCount), grass_dispersion_min_(grassDispersionMin), grass_dispersion_max_(grassDispersionMax), grass_density_(grassDensity) {
}


void GenerateComplexMap::operator() ( Matrix< Tile >& map ) {
	LOG("ComplexMapGenerate:\n"
        "               size = (%u, %u)\n"
        "               grassGroupCount = %u\n"
        "               grassDispersionMin = %lg\n"
        "               grassDispersionMax = %lg\n"
        "               grassDensity = %lg",
        map.getHeight(), map.getWidth(),
        grass_group_count_, grass_dispersion_min_, grass_dispersion_max_, grass_density_);
  
	// Размеры поля
    unsigned mapHeight  = map.getHeight();
    unsigned mapWidth   = map.getWidth();
	
	// Заполнение водой
    for (unsigned i = 0; i < mapHeight; i++)
        for (unsigned j = 0; j < mapWidth; j++)
            map.at(i, j).setID(TILE_WATER_ID);
		
	// Относительное положение центра травы
    std::uniform_real_distribution< double >    grassCentreDistribution(0, 1);
    
	for (unsigned i = 0; i < grass_group_count_; i++) {
		// Координаты текущего центра
        double xCoord = grassCentreDistribution(mtGenerator);
        double yCoord = grassCentreDistribution(mtGenerator);
		
		addIsland( map, xCoord, yCoord, 1, true, TILE_GRASS_ID);
	}
	
	for (unsigned i = 0; i * 3 < grass_group_count_ * 2; i++) {
		// Координаты текущего центра
        double xCoord = grassCentreDistribution(mtGenerator);
        double yCoord = grassCentreDistribution(mtGenerator);
		
		addIsland( map, xCoord, yCoord, 0.3, true, TILE_WATER_ID);
	}
	
	for (unsigned i = 0; i < grass_group_count_ * 4; i++) {
		// Координаты текущего центра
        double xCoord = grassCentreDistribution(mtGenerator);
        double yCoord = grassCentreDistribution(mtGenerator);
		
		addIsland( map, xCoord, yCoord, 1.0 / 7.0, false, TILE_GRASS_ID);
	}
    
    GenerateMap::fancyEdges(map);
}


void GenerateComplexMap::addIsland ( Matrix< Tile >& map, 
									 double xCoord, double yCoord, 
									 double dispersionParameter, 
									 bool independent, int tile_type_id) {
	
		std::uniform_real_distribution< double >  grassDispersionDistribution(grass_dispersion_min_ * dispersionParameter, 
																				grass_dispersion_max_ * dispersionParameter);
		
		std::normal_distribution< double > xGrassDistribution(xCoord, grassDispersionDistribution(mtGenerator));
        std::normal_distribution< double > yGrassDistribution(yCoord, grassDispersionDistribution(mtGenerator));
        
		unsigned mapHeight = map.getHeight(), mapWidth = map.getWidth();
		
        for (unsigned j = 0; (double)j * grass_density_ < (double)(mapHeight * mapWidth); j++) {
            
            if (independent && j == 0) {
                int xGenerated = static_cast< int >(xCoord * mapHeight);
                int yGenerated = static_cast< int >(yCoord * mapWidth);
                
                map.at(xGenerated, yGenerated).setID( tile_type_id );
            }
            else {
                double xCurrent = xGrassDistribution(mtGenerator);
                double yCurrent = yGrassDistribution(mtGenerator);
                
                if (xCurrent >= 1 || xCurrent < 0 || yCurrent >= 1 || yCurrent < 0) // Трава сгенерировалась за пределами карты
                    continue;
                
                int xGenerated = static_cast< int >(xCurrent * mapHeight);
                int yGenerated = static_cast< int >(yCurrent * mapWidth);
                
                bool flag = false;
                
                if (xGenerated > 0 && map.at( xGenerated - 1, yGenerated ).getID() == tile_type_id)
                    flag = true;
                else if (xGenerated + 1 < (int)mapHeight && map.at( xGenerated + 1, yGenerated ).getID() == tile_type_id)
                    flag = true;
                else if (yGenerated > 0 && map.at( xGenerated, yGenerated - 1 ).getID() == tile_type_id)
                    flag = true;
                else if (yGenerated + 1 < (int)mapWidth && map.at( xGenerated, yGenerated + 1 ).getID() == tile_type_id)
                    flag = true;
                
                if (flag)
                    map.at( xGenerated, yGenerated ).setID( tile_type_id );
            }
        }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

GenerateConnetedMap::GenerateConnetedMap ( unsigned int grassGroupCount, double grassDispersionMin, double grassDispersionMax, double grassDensity ) :
	GenerateMap(), 
    grass_group_count_(grassGroupCount), grass_dispersion_min_(grassDispersionMin), grass_dispersion_max_(grassDispersionMax), grass_density_(grassDensity) {
    
}

void GenerateConnetedMap::operator() ( Matrix< Tile >& map ) {
     LOG("ConnectedMapGenerate:\n"
        "               size = (%u, %u)\n"
        "               grassGroupCount = %u\n"
        "               grassDispersionMin = %lg\n"
        "               grassDispersionMax = %lg\n"
        "               grassDensity = %lg",
        map.getHeight(), map.getWidth(),
        grass_group_count_, grass_dispersion_min_, grass_dispersion_max_, grass_density_);
  
    // Размеры поля
    unsigned mapHeight  = map.getHeight();
    unsigned mapWidth   = map.getWidth();
    
    // Относительное положение центра травы
    std::uniform_real_distribution< double >    grassCentreDistribution(0, 1);
    std::uniform_real_distribution< double >    grassDispersionDistribution(grass_dispersion_min_, grass_dispersion_max_);
    
    for (unsigned i = 0; i < mapHeight; i++)
        for (unsigned j = 0; j < mapWidth; j++)
            map.at(i, j).setID(TILE_WATER_ID);
    
    for (unsigned i = 0; i < grass_group_count_; i++) {
        
        // Координаты текущего центра
        double xCoord = grassCentreDistribution(mtGenerator);
        double yCoord = grassCentreDistribution(mtGenerator);
        
        // Распределения травы вокруг центра
        std::normal_distribution< double > xGrassDistribution(xCoord, grassDispersionDistribution(mtGenerator));
        std::normal_distribution< double > yGrassDistribution(yCoord, grassDispersionDistribution(mtGenerator));
        
        for (unsigned j = 0; (double)j * grass_density_ < (double)(mapHeight * mapWidth); j++) {
            
            if (j == 0) {
                int xGenerated = static_cast< int >(xCoord * mapHeight);
                int yGenerated = static_cast< int >(yCoord * mapWidth);
                
                map.at(xGenerated, yGenerated).setID( TILE_GRASS_ID );
            }
            else {
                double xCurrent = xGrassDistribution(mtGenerator);
                double yCurrent = yGrassDistribution(mtGenerator);
                
                if (xCurrent >= 1 || xCurrent < 0 || yCurrent >= 1 || yCurrent < 0) // Трава сгенерировалась за пределами карты
                    continue;
                
                int xGenerated = static_cast< int >(xCurrent * mapHeight);
                int yGenerated = static_cast< int >(yCurrent * mapWidth);
                
                bool flag = false;
                
                if (xGenerated > 0 && map.at( xGenerated - 1, yGenerated ).getID() == TILE_GRASS_ID)
                    flag = true;
                else if (xGenerated + 1 < (int)mapHeight && map.at( xGenerated + 1, yGenerated ).getID() == TILE_GRASS_ID)
                    flag = true;
                else if (yGenerated > 0 && map.at( xGenerated, yGenerated - 1 ).getID() == TILE_GRASS_ID)
                    flag = true;
                else if (yGenerated + 1 < (int)mapWidth && map.at( xGenerated, yGenerated + 1 ).getID() == TILE_GRASS_ID)
                    flag = true;
                
                if (flag)
                    map.at( xGenerated, yGenerated ).setID( TILE_GRASS_ID );
            }
        }
    }
    GenerateMap::fancyEdges(map);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


MapDump::MapDump() {
}

void MapDump::operator() ( Matrix< Tile >& map, std::vector< Entity>& En ) {
    
    Matrix< int > IDS(map.getHeight(), map.getWidth());
    for (unsigned i = 0; i < map.getHeight(); i++)
        for (unsigned j = 0; j < map.getWidth(); j++) {
            IDS.at(i, j) = map.at(i, j).getID();
        }
    for (auto & iter: En) {
        IDS.at(iter.getTileFrom().x, iter.getTileFrom().y) = iter.getID();
    }
    
    for (unsigned i = 0; i < IDS.getHeight(); i++) {
        for (unsigned j = 0; j < IDS.getWidth(); j++) {
            switch (IDS.at(i, j)) {
                case OBJECT_GRASS_EATING_ID:
                    std::cout << CL_BG_PURPLE;
                    break;
                case OBJECT_PREDATOR_ID:
                    std::cout << CL_BG_RED;
                    break;
                case TILE_WATER_ID:
                    std::cout << CL_BG_BLUE;
                    break;
                case TILE_GRASS_ID:
                    std::cout << CL_BG_GREEN;
                    break;
                default:
                    std::cout << CL_BG_BLACK;
            }
            std::cout << "  " << TY_FT_DEFAULT; 
        }
        std::cout << std::endl;
    }
}
//*/

