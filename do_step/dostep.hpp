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
    std::shared_ptr<const ModelManager> model_manager_;
    Matrix< int > cache_;
    std::vector< int > color_;
    
    void initializationStage( Matrix< Tile >& map, std::vector< Entity >& En );
    void huntingStage( Matrix< Tile >& map, std::vector< Entity >& En );
    void grassEatingMovingStage( Matrix< Tile >& map, std::vector< Entity >& En );
    void predatorsMovingStage( Matrix< Tile >& map, std::vector< Entity >& En );
    void deleteCorpses( Matrix< Tile >& map, std::vector< Entity >& En );
    void multiplicationStage( Matrix< Tile >& map, std::vector< Entity >& En );
    
public:
    RandomMoving(std::shared_ptr<const ModelManager> model_manager_);
    void operator () ( Matrix< Tile >& map, std::vector< Entity >& En );
};


#endif
