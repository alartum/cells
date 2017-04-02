#ifndef HEADER_DOSTEP_HPP_INCLUDED
#define HEADER_DOSTEP_HPP_INCLUDED

#include <vector>
#include <random>
#include "../object/object.hpp"

// Абстрактный класс алгоритма обработки поля для следующего шага
class DoStep
{
public:
    DoStep();
    // Функция шага
    virtual void operator () (std::vector< Object* > & M);
};

#endif
