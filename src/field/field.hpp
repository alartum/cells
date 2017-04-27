#ifndef HEADER_FIELD_HPP_INCLUDED
#define HEADER_FIELD_HPP_INCLUDED
#include <functional>

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
#include "../do_step/dostep.hpp"

class Field 
{
public:
    sf::RenderWindow&           mWindow;
    sf::Vector2u&               mSizeTiles;
    unsigned                    mTileSize;
    
    // Objects on the field
    std::vector< Object* >      mObjects;
    Matrix<Tile>                mMap;
    
    std::shared_ptr<const ModelManager> mModelManager;

public:    
    // fSizeTiles
    Field(  sf::RenderWindow&   Window,
            sf::Vector2u&       sizeTiles,
            unsigned            mTileSize
         );
    
    // Деструктор
    ~Field();
    
    // Вернуть ссылку на привязанное окно
    sf::RenderWindow& getWindow();
    
    unsigned getWidth();
    unsigned getHeight();
    sf::Vector2u getSize();

    // Открыто ли привязанное окно
    bool isWindowOpen();
    
    // Активность привязанного окна
    void setActive(bool status);
    
    // Установить менеджер моделей
    void setModelManager (const std::shared_ptr<const ModelManager>& modelManagerPtr);

    // Вывести на W все объекты (вызвать draw(W) для них)
    void draw();
    
    // Отрисовать только объекты
    void drawObjects();

    // Отрисовать только тайлы
    void drawTiles();
    
    // Вызвать метод display привязанного окна
    void display();
        
    // Функция генерации тайлов поля
    void generateTiles(std::function< void(Matrix< Tile >&) > generatorMap);
    
    // Функция генерации объектов на поле
    void generateObjects(std::function< void(Matrix< Tile >&, std::vector< Object* >&) > generatorObjects);
    
    // Функция пересчета состояния поля на один игровой шаг
    void doStep();
};

#endif
