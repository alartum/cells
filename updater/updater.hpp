#ifndef UPDATER_HPP
#define UPDATER_HPP

#include "../object/object.hpp"

// Абстрактный класс алгоритма обработки поля для следующего шага
class Updater
{
public:
    Updater();
    // Функция шага
    virtual void operator () (std::vector< Object > & M);
};

#endif //UPDATER_HPP
