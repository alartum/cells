#ifndef HEADER_GENERATEOBJECTS_HPP_INCLUDED
#define HEADER_GENERATEOBJECTS_HPP_INCLUDED

#include <exception>
#include <stdexcept>

#include <SFML/Graphics.hpp>

#include "../matrix/matrix.hpp"
#include "../object/object.hpp"
#include "../tile/tile.hpp"
#include "../entity/entity.hpp"


// Абстрактный генератор карт
class GenerateObjects
{
public:
    GenerateObjects();
    virtual void operator () (Matrix<Tile>& map, std::vector< Entity >& R);
};



class GenerateRandomEntity : public GenerateObjects {
private:
    double      grassEatingDensity;
    unsigned    grassEatingDistance;
    unsigned    grassEatingNeightborsMin;
    unsigned    grassEatingNeightborsMax;
    
    double      predatorsDensity;
    unsigned    predatorsDistance;
    unsigned    predatorNeightborsMin;
    unsigned    predatorNeightborsMax;
    
public:
    GenerateRandomEntity(       double      grassEatingDensity,
                                unsigned    grassEatingDistance,
                                unsigned    grassEatingNeightborsMin,
                                unsigned    grassEatingNeightborsMax,
    
                                double      predatorsDensity,
                                unsigned    predatorsDistance,
                                unsigned    predatorNeightborsMin,
                                unsigned    predatorNeightborsMax
    );
    
    void operator () (Matrix<Tile>& map, std::vector< Entity >& R);
};


#endif
//*/