#ifndef HEADER_STEP_ALGORITHM_HPP_INCLUDED
#define HEADER_STEP_ALGORITHM_HPP_INCLUDED

#include <vector>

#include "../object/object.hpp"

// Абстрактный класс алгоритма обработки поля для следующего шага
class StepAlgorithm
{
public:
    StepAlgorithm();
    // Функция шага
    virtual int step (std::vector< Object > & M) = 0;
};
/*
// Наследник StepAlgorithm, реализующий игру "Жизнь"
class LifeAlgorithm : public StepAlgorithm
{
public:
    LifeAlgorithm();
    // Функция шага
    int step (std::vector< Object > & M);
};
*/

#endif