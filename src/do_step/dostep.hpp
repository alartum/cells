#ifndef HEADER_DOSTEP_HPP_INCLUDED
#define HEADER_DOSTEP_HPP_INCLUDED

#include <vector>
#include <random>
#include "../object/object.hpp"
#include "../matrix/matrix.hpp"
#include "../tile/tile.hpp"
#include "../entity/entity.hpp"

class DoStep
{
public:
    DoStep();
    // Функция шага
    virtual void operator () (Matrix< Tile >& map, std::vector< Entity >& M);
};


#endif
