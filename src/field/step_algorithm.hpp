#ifndef HEADER_STEP_ALGORITHM_HPP_INCLUDED
#define HEADER_STEP_ALGORITHM_HPP_INCLUDED

#include "../cell/cell.hpp"
#include "../matrix/matrix.hpp"

// Абстрактный класс алгоритма обработки поля для следующего шага
class StepAlgorithm
{
public:
    StepAlgorithm();
    // Функция шага
    virtual int step (Matrix< Cell > & M) = 0;
};

// Наследник StepAlgorithm, реализующий игру "Жизнь"
class LifeAlgorithm : public StepAlgorithm
{
public:
    LifeAlgorithm();
    // Функция шага
    int step (Matrix< Cell > & M);
};


#endif