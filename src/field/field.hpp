#ifndef HEADER_FIELD_HPP_INCLUDED
#define HEADER_FIELD_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "../tile/tile.hpp"
#include "../matrix/matrix.hpp"
#include "../object/object.hpp"
#include "../generate_objects/generateobjects.hpp"
#include "../generate_map/generatemap.hpp"
#include "../do_step/dostep.hpp"
#include "../model_manager/modelmanager.hpp"

class Field 
{
private:
    Matrix<Tile>     mMap;
    ModelManager     mModelManager;
    // In pixels
    sf::Vector2u     mSizePixels;
    sf::RenderWindow mWindow;
    // Objects on the field
    std::vector< Object* > mObjects;

    GenerateMap&     mGenerateMap;
    GenerateObjects& mGenerateObjects;
    DoStep&          mDoStep;

public:    
    // fSizeTile
    Field(sf::Vector2u sizeTile, GenerateObjects& generateObjects,
          GenerateMap& generateMap, DoStep& doStep);
    
    // Деструктор
    ~Field();
    
    sf::RenderWindow& getWindow();

    // Открыто ли привязанное окно
    bool isWindowOpen();
    
    // Активность привязанного окна
    void setActive( bool status );

    // Вывести на W все объекты (вызвать draw(W) для них)
    void draw();

    void drawObjects();

    void drawTiles();
    
    // Вызвать метод display привязанного окна
    void display();
        
    // Функция генерации поля, принимает ссылку на генератор
    void generate();

    // Функция пересчета состояния поля на один игровой шаг
    void doStep();
};

#endif
