#ifndef HEADER_STEP_ALGORITHM_HPP_INCLUDED
#define HEADER_STEP_ALGORITHM_HPP_INCLUDED

#include <vector>
#include <random>

#include "../object/object.hpp"

// Абстрактный класс алгоритма обработки поля для следующего шага
class StepAlgorithm
{
public:
    StepAlgorithm();
    // Функция шага
    virtual int action (std::vector< Object* > & M) = 0;
};

class RandomMoving : public StepAlgorithm
{
private:
    sf::Vector2i fSize;
public:
    RandomMoving( sf::Vector2i fSize );
    int action (std::vector< Object* > & M);
};

#endif