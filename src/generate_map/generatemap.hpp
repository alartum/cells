#ifndef GENERATEMAP_HPP
#define GENERATEMAP_HPP

#include "../matrix/matrix.hpp"
#include "../tile/tile.hpp"
#include "../tileinfo/tile_ids.hpp"
#include "../entity/entity.hpp"
class GenerateMap
{
public:
    GenerateMap();
    void operator () (Matrix<Tile>& map);
};

class GenerateRandomMap : public GenerateMap
{
// Генерация островков травы с помощью нормального распределения с диагональной 
// ковариационной матрицей, значения которой распределены равнометрно между
// grassDispersionMin, grassDispersionMax.
// Плотность распределения островков равномерная.
// Тип генерируемой карты не зависит от размера пареданной "Matrix< Tile >& map". 
protected:
    unsigned    grassGroupCount;        // Количество островков "травы"
    double      grassDispersionMin;     // Дисперсия "травы" (минимальное значени)
    double      grassDispersionMax;     // Дисперсия "травы" (максимальное значение)
    double      grassDensity;           // Плотность "травяных" островков (положительное число около 7-20, 7 - наиболее плотная)
public:
    GenerateRandomMap(unsigned grassGroupCount, double grassDispersionMin, double grassDispersionMax, double grassDensity);
    void operator ()(Matrix<Tile>& map);
};




class MapDump 
{
public:
    MapDump();
    void operator () ( Matrix< Tile >& map, std::vector< Entity> & En );
};



#endif // GENERATEMAP_HPP
