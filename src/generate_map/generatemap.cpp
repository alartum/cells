#include "generatemap.hpp"
#include <random>
#include <numeric>
#include <iterator>
#include <algorithm>

#define DEBUG
#include "../debug.h"

GenerateMap::GenerateMap() {
    ;
}

void GenerateMap::operator() ( Matrix< Tile >& map ) {
    //std::cout << "ЗаебалоСюдаХодить" << std::endl;;
}




GenerateRandomMap::GenerateRandomMap (unsigned grassGroupCount, double grassDispersionMin, double grassDispersionMax, double grassDensity ) :
    grassGroupCount(grassGroupCount), grassDispersionMin(grassDispersionMin), grassDispersionMax(grassDispersionMax), grassDensity(grassDensity) 
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
        grassGroupCount, grassDispersionMin, grassDispersionMax, grassDensity);
  
    // Размеры поля
    unsigned mapHeight  = map.getHeight();
    unsigned mapWidth   = map.getWidth();
    
    // Вспомогательные генераторы
    std::random_device  tempRandomDevice;
    std::mt19937        mtGenerator(tempRandomDevice());
    
    // Относительное положение центра травы
    std::uniform_real_distribution< double >    grassCentreDistribution(0, 1);
    std::uniform_real_distribution< double >    grassDispersionDistribution(grassDispersionMin, grassDispersionMax);
    
    for (unsigned i = 0; i < mapHeight; i++)
        for (unsigned j = 0; j < mapWidth; j++)
            map.at(i, j).setTypeID(TILE_WATER_ID);
    
    for (unsigned i = 0; i < grassGroupCount; i++) {
        
        // Координаты текущего центра
        double xCoord = grassCentreDistribution(mtGenerator);
        double yCoord = grassCentreDistribution(mtGenerator);
        
        // Распределения травы вокруг центра
        std::normal_distribution< double > xGrassDistribution(xCoord, grassDispersionDistribution(mtGenerator));
        std::normal_distribution< double > yGrassDistribution(yCoord, grassDispersionDistribution(mtGenerator));
        
        for (unsigned j = 0; (double)j * grassDensity < (double)(mapHeight * mapWidth); j++) {
            double xCurrent = xGrassDistribution(mtGenerator);
            double yCurrent = yGrassDistribution(mtGenerator);
            
            if (xCurrent >= 1 || xCurrent < 0 || yCurrent >= 1 || yCurrent < 0) // Трава сгенерировалась за пределами карты
                continue;
            
            map.at(
                static_cast< unsigned >(xCurrent * mapHeight), 
                static_cast< unsigned >(yCurrent * mapWidth)
            ).setTypeID(TILE_GRASS_ID);
        }
    }
}




GenerateConnetedMap::GenerateConnetedMap ( unsigned int grassGroupCount, double grassDispersionMin, double grassDispersionMax, double grassDensity ) :
    grassGroupCount(grassGroupCount), grassDispersionMin(grassDispersionMin), grassDispersionMax(grassDispersionMax), grassDensity(grassDensity) {
    
}

void GenerateConnetedMap::operator() ( Matrix< Tile >& map ) {
     LOG("ConnectedMapGenerate:\n"
        "               size = (%u, %u)\n"
        "               grassGroupCount = %u\n"
        "               grassDispersionMin = %lg\n"
        "               grassDispersionMax = %lg\n"
        "               grassDensity = %lg",
        map.getHeight(), map.getWidth(),
        grassGroupCount, grassDispersionMin, grassDispersionMax, grassDensity);
  
    // Размеры поля
    unsigned mapHeight  = map.getHeight();
    unsigned mapWidth   = map.getWidth();
    
    // Вспомогательные генераторы
    std::random_device  tempRandomDevice;
    std::mt19937        mtGenerator(tempRandomDevice());
    
    // Относительное положение центра травы
    std::uniform_real_distribution< double >    grassCentreDistribution(0, 1);
    std::uniform_real_distribution< double >    grassDispersionDistribution(grassDispersionMin, grassDispersionMax);
    
    for (unsigned i = 0; i < mapHeight; i++)
        for (unsigned j = 0; j < mapWidth; j++)
            map.at(i, j).setTypeID(TILE_WATER_ID);
    
    for (unsigned i = 0; i < grassGroupCount; i++) {
        
        // Координаты текущего центра
        double xCoord = grassCentreDistribution(mtGenerator);
        double yCoord = grassCentreDistribution(mtGenerator);
        
        // Распределения травы вокруг центра
        std::normal_distribution< double > xGrassDistribution(xCoord, grassDispersionDistribution(mtGenerator));
        std::normal_distribution< double > yGrassDistribution(yCoord, grassDispersionDistribution(mtGenerator));
        
        for (unsigned j = 0; (double)j * grassDensity < (double)(mapHeight * mapWidth); j++) {
            
            if (j == 0) {
                int xGenerated = static_cast< int >(xCoord * mapHeight);
                int yGenerated = static_cast< int >(yCoord * mapWidth);
                
                map.at(xGenerated, yGenerated).setTypeID( TILE_GRASS_ID );
            }
            else {
                double xCurrent = xGrassDistribution(mtGenerator);
                double yCurrent = yGrassDistribution(mtGenerator);
                
                if (xCurrent >= 1 || xCurrent < 0 || yCurrent >= 1 || yCurrent < 0) // Трава сгенерировалась за пределами карты
                    continue;
                
                int xGenerated = static_cast< int >(xCurrent * mapHeight);
                int yGenerated = static_cast< int >(yCurrent * mapWidth);
                
                bool flag = false;
                
                if (xGenerated > 0 && map.at( xGenerated - 1, yGenerated ).getTypeID() == TILE_GRASS_ID)
                    flag = true;
                else if (xGenerated + 1 < mapHeight && map.at( xGenerated + 1, yGenerated ).getTypeID() == TILE_GRASS_ID)
                    flag = true;
                else if (yGenerated > 0 && map.at( xGenerated, yGenerated - 1 ).getTypeID() == TILE_GRASS_ID)
                    flag = true;
                else if (yGenerated + 1 < mapWidth && map.at( xGenerated, yGenerated + 1 ).getTypeID() == TILE_GRASS_ID)
                    flag = true;
                
                if (flag)
                    map.at( xGenerated, yGenerated ).setTypeID( TILE_GRASS_ID );
            }
        }
    }
}





MapDump::MapDump() {
}

void MapDump::operator() ( Matrix< Tile >& map, std::vector< Entity>& En ) {
    
    Matrix< int > IDS(map.getHeight(), map.getWidth());
    for (unsigned i = 0; i < map.getHeight(); i++)
        for (unsigned j = 0; j < map.getWidth(); j++) {
            IDS.at(i, j) = map.at(i, j).getTypeID();
        }
    for (auto & iter: En) {
        IDS.at(iter.getTileFrom().x, iter.getTileFrom().y) = iter.getTypeID();
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


