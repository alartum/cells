#ifndef GENERATEMAP_HPP
#define GENERATEMAP_HPP

#include <random>
#include <iostream>
#include <numeric>
#include <vector>
#include <functional>

#include "../matrix/matrix.hpp"
#include "../tile/tile.hpp"
#include "../config/tile_ids.hpp"
#include "../entity/entity.hpp"

class GenerateMap {
protected:
    void fancyEdges(Matrix<Tile> &map);
    int  getEdgeType(Matrix< Tile >& map, unsigned y, unsigned x);

    std::minstd_rand        mtGenerator;
public:
    GenerateMap();
    void operator () ( Matrix<Tile>& map );
};

class GenerateRandomMap : public GenerateMap {

// Генерация островков травы с помощью нормального распределения с диагональной
// ковариационной матрицей, значения которой распределены равнометрно между
// grassDispersionMin, grassDispersionMax.
// Плотность распределения островков равномерная.
// Тип генерируемой карты не зависит от размера пареданной "Matrix< Tile >& map".
protected:
    unsigned    grass_group_count_;        // Количество островков "травы"
    double      grass_dispersion_min_;     // Дисперсия "травы" (минимальное значени)
    double      grass_dispersion_max_;     // Дисперсия "травы" (максимальное значение)
    double      grass_density_;           // Плотность "травяных" островков (положительное число около 7-20, 7 - наиболее плотная)
public:
    GenerateRandomMap ( unsigned grass_group_count_, double grass_dispersion_min_, double grass_dispersion_max_, double grass_density_ );
    void operator () ( Matrix<Tile>& map );
};

class GenerateConnetedMap : public GenerateMap {
// Карта с высокой степенью связности
protected:
    unsigned    grass_group_count_;        // Количество островков "травы"
    double      grass_dispersion_min_;     // Дисперсия "травы" (минимальное значени)
    double      grass_dispersion_max_;     // Дисперсия "травы" (максимальное значение)
    double      grass_density_;            // Плотность "травяных" островков (положительное число около 7-20, 7 - наиболее плотная)
public:
    GenerateConnetedMap( unsigned grass_group_count_, double grass_dispersion_min_, double grass_dispersion_max_, double grass_density_ );
    void operator () ( Matrix<Tile>& map );
};

class GenerateComplexMap : public GenerateMap {
private:
    void addIsland ( Matrix< Tile >& map, double xCoord, double yCoord, double dispersionParameter, bool independent, int tile_type_id);
// Карта со сложными контурами имеющаяя высокий уровень связности.
protected:
    unsigned    grass_group_count_;        // Количество островков "травы"
    double      grass_dispersion_min_;     // Дисперсия "травы" (минимальное значени)
    double      grass_dispersion_max_;     // Дисперсия "травы" (максимальное значение)
    double      grass_density_;            // Плотность "травяных" островков (положительное число около 7-20, 7 - наиболее плотная)
public:
    GenerateComplexMap( unsigned grass_group_count_, double grass_dispersion_min_, double grass_dispersion_max_, double grass_density_ );
    void operator () ( Matrix<Tile>& map );
};

class MapDump {
public:
    MapDump();
    void operator () ( Matrix< Tile >& map, std::vector< Entity> & En );
};



#endif // GENERATEMAP_HPP

