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
    double      grasseating_density_;
    unsigned    grasseating_distance_;
    unsigned    grasseating_neightbors_min_;
    unsigned    grasseating_neightbors_max_;
    
    double      predators_density_;
    unsigned    predators_distance_;
    unsigned    predator_neightbors_min_;
    unsigned    predator_neightbors_max_;
    
public:
    GenerateRandomEntity(       double      grasseating_density,
                                unsigned    grasseating_distance,
                                unsigned    grasseating_neightbors_min,
                                unsigned    grasseating_neightbors_max,
    
                                double      predators_density,
                                unsigned    predators_distance,
                                unsigned    predator_neightbors_min,
                                unsigned    predator_neightbors_max
    );
    
    void operator () (Matrix<Tile>& map, std::vector< Entity >& R);
};


#endif
//*/
