/*#include "field.hpp"


 // Конструктор W - окно отрисовки, fSize - вектор размера, fCellSize - размер клетки
Field::Field(sf::Vector2u sizeTile, GenerateObjects& generateObjects,
             GenerateMap& generateMap, DoStep &doStep) 
{
    //mWindow.clear(sf::Color::White);
}

// Деструктор
Field::~Field() {
    for (auto iter: mObjects)
        delete iter;
}

// Открыто ли привязанное окно
bool Field::isWindowOpen() {
    return mWindow.isOpen();
}

// Активность привязанного окна
void Field::setActive( bool status ) {
    mWindow.setActive(status);
}

// Вызвать метод display привязанного окна
void Field::display() {
    mWindow.display();
}


// Вывести на W состояния клеток, не выполняется для тех клеток, для которых cType == cPrevType (которые не изменили тип)
void Field::draw()
{
    drawTiles();
    drawObjects();
}
    
// Функция генерации поля, принимает тип генерируемого поля
void Field::generate()
{
    mGenerateMap(mMap);
    mGenerateObjects(mMap, mObjects);
}

// Функция пересчета состояния поля на один игровой шаг
void Field::doStep()
{
    mDoStep(mObjects);
}


void Field::drawObjects()
{
    for (auto & objectIterator : mObjects)
        objectIterator->draw(mWindow);

}

void Field::drawTiles()
{
    for (unsigned x = 0; x < mMap.getWidth(); x++){
        for (unsigned y = 0; y < mMap.getWidth(); y++){
            Tile& current = mMap.at(x, y);
            if (current.isUpdated()){
                mWindow.draw(current.getSprite());
                current.setUpdated(false);
            }
        }
    }
}

sf::RenderWindow &Field::getWindow()
{
    return mWindow;
}*/
