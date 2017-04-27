#ifndef GENERATEMAP_HPP
#define GENERATEMAP_HPP

#include "../matrix/matrix.hpp"
#include "../tile/tile.hpp"
/*
class GenerateMap
{
public:
    GenerateMap();
    // Generate field
    virtual void operator () (Matrix<Tile>& map);
};
*/
class GenerateRandomMap// : public GenerateMap
{
// Генерация островков травы с помощью нормального распределения с диагональной 
// ковариационной матрицей, значения которой распределены равнометрно между
// grassDispersionMin, grassDispersionMax.
// Плотность распределения островков равномерная.
// Тип генерируемой карты не зависит от размера пареданной "Matrix< Tile >& map". 
protected:
    unsigned    grassGroupCount;        // Количество "островков травы"
    double      grassDispersionMin;     // Дисперсия травы (минимальное значени)
    double      grassDispersionMax;     // Дисперсия травы (максимальное значение)
    double      grassDensity;           // Плотность травяных островков (положительное число около 7-20, 7 - наиболее плотная)
public:
    GenerateRandomMap(unsigned grassGroupCount, double grassDispersionMin, double grassDispersionMax, double grassDensity);
    void operator ()(Matrix<Tile>& map);
};

#endif // GENERATEMAP_HPP
