#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../object/object.hpp"
#include "../../../cells2/cells/src/tile/tile.hpp"

class Entity : public Object
{
public:
    Entity(int entityType = 0,
           const sf::Vector2f& position = sf::Vector2f(0,0),
           unsigned state = 0);
    // void setState (State state);
    // State getState() const;
};


/*
class EntityInterface : public Object {
public:
    // For drawing
    sf::Vector2u positionOnTiles;
    sf::Vector2u nextPositionAnimation;
    
    // For doStep
    sf::Vector2u nextPositionAlgorithm;
};
*/
/*
    Предлагается изменить класс Entity:
Хранить: 
    sf::Vector2u positionOnTiles; - позиция в начале текущего шага
    sf::Vector2u nextPositionAnimation; - позиция, на которую производится движение на данном шаге
    
    sf::Vector2u nextPositionAlgorithm; - поле, в которое doStep пишет план еще на шаг вперед
    
    и отдельно хранить поле sf::Vector2f position, которое наследуется от спрайта
И аналогично для класса Tile
    int currentTypeID
    int nextTypeId
    
    игровой цикл реализовать так
    
    while (1) {
        // некоторым образом инициализированно Matrix< Tile > и vector< Entity >
        Создать два потока:
            Первый:
                Поток отрисовки, в течение скажем 5 условных тактов отрисовывает передвижение
                модели Entity из позиции positionOnTiles на полу в nextPositionAnimation, каждый раз пересчитывая
                vector2f position
            Второй:
                Предполагая, что все Entity находятся уже в sf::Vector2u nextPositionAnimation рассчитать для них
                nextPositionAlgorithm еще на ход вперед, а для Тайлов рассчитывает nextTypeID
        JOIN
        Для всех Entity:
            positionOnTiles <- nextPositionAnimation
            nextPositionAnimation <- nextPositionAlgorithm
        Для всех Тайлов:
            currentTypeID <- nextTypeID
    }
    
    Таким образом, можно разделить вычисление следующего хода и отрисовку текущего
*/



#endif // ENTITY_HPP
