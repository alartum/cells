#include <vector>
#include <random>
#include "../object/object.hpp"

#ifndef HEADER_DOSTEP_HPP_INCLUDED
#define HEADER_DOSTEP_HPP_INCLUDED


// Абстрактный класс алгоритма обработки поля для следующего шага
class DoStep
{
public:
    DoStep();
    // Функция шага
    virtual void operator () (std::vector< Object* > & M);
};

class RandomMoving : public DoStep
{
private:
    sf::Vector2i fSize;
public:
    RandomMoving( sf::Vector2i fSize );
    void operator () (std::vector< Object* >& M);
};

#endif
