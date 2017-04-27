#ifndef OBJECTGENERATOR_HPP
#define OBJECTGENERATOR_HPP

#include "../matrix/matrix.hpp"
#include "../object/object.hpp"
#include "../tile/tile.hpp"

class ObjectGenerator
{
public:
    ObjectGenerator();
    virtual void operator () (const Matrix<Tile>& map, std::vector<Object>& R);
};

#endif //OBJECTGENERATOR_HPP
