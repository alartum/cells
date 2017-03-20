/*#include "generator.hpp"

#include <random>
#include <set>
////////////////////////////////////////////////////////////////////////////////////////////////

FieldGenerator::FieldGenerator(sf::Vector2u fSize) : fSize(fSize)
{
}
////////////////////////////////////////////////////////////////////////////////////////////////
UniformRandomFieldGenerator::UniformRandomFieldGenerator (sf::Vector2u fSize, double probability ) 
    : FieldGenerator ( fSize ), probability(probability)
{
    if (probability > 1 || probability < 0)
        throw std::invalid_argument("probability mustn't be greater then 1 and less then 0");
}

void UniformRandomFieldGenerator::generate(Matrix< Cell > & R) {
    R.setSize(fSize.x, fSize.y);
    for (unsigned i = 1; i + 1 < fSize.y; i++)
        for (unsigned j = 1; j + 1 < fSize.x; j++)
            R.at(i, j) = Cell( ((double)rand() / RAND_MAX) < probability ? Cell::Live : Cell::Clear );
    return;
}
////////////////////////////////////////////////////////////////////////////////////////////////
*/
