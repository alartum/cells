#ifndef HEADER_OBJECT_HPP_INCLUDED
#define HEADER_OBJECT_HPP_INCLUDED

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>
#include <cmath>

// Абстрактный класс, представляющий объект с поля
class Object 
{
public:
    // Возможные типы объектов
    enum object_type_t {None, Water, Grass};
    
protected:
    object_type_t oType;
    
public:
    virtual ~Object();
    
    // Нарисовать объект в окне W
    virtual void draw(sf::RenderWindow & W) = 0;
    
    // Вернуть тип объекта
    object_type_t getType() const;
    
    // Операторы присваивания
    Object& operator = (Object const & Other);
    Object& operator = (Object const && Other);
    
    // Оператор вывода
    friend std::ostream& operator<< (std::ostream& ostr, const Object & O) {
        return (ostr << "Object: " << ((int)O.oType));
    }
};

// Класс круглого куска травы
class Grass : public Object
{
public:
    // Расположение и радиус куска травы
    sf::Vector2i gLocation;
    double gRadius;
public:
    // Конструктор по расположению и радиусу
    Grass(sf::Vector2i gLocation, double gRadius);
    // Копирующие конструкторы
    Grass(Grass& Other);
    Grass(Grass&& Other);
    //Деструктор
    ~Grass();
    
    // Нарисовать объект в окне W
    void draw(sf::RenderWindow& W);
    
    // Проверка пересечения
    bool isIntersect( Grass& Other );
    
    // Операторы присваивания
    Grass& operator = (Grass const & Other);
    Grass& operator = (Grass const && Other);
};

#endif