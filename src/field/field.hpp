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

class Field : public sf::RenderWindow
{
public:
    sf::Vector2u                mTileSize;
    
    // Objects on the field
    std::vector< Object* >      mObjects;
    Matrix<Tile>                mMap;
    
    std::shared_ptr<const ModelManager> mModelManager;

    void setTilePositions();
public:    
    Field(sf::Vector2u sizeInTiles, sf::Vector2u sizeInPixels, sf::Vector2u tileSize);
    
    ~Field();
    void fitView();
    // Sets model manager for every tile
    void loadTileTextures();
    void setMapSize(sf::Vector2u size);
    sf::Vector2u getMapSize() const;
    void setTileSize(sf::Vector2u size);
    sf::Vector2u getTileSize() const;
    void setModelManager (const std::shared_ptr<const ModelManager>& modelManagerPtr);

    // Отрисовать только объекты
    void drawObjects();

    // Отрисовать только тайлы
    void drawTiles();
        
    // Функция генерации тайлов поля
    void generateTiles(std::function< void(Matrix< Tile >&) > generatorMap);
    
    // Функция генерации объектов на поле
    void generateObjects(std::function< void(Matrix< Tile >&, std::vector< Object* >&) > generatorObjects);
    
    // Функция пересчета состояния поля на один игровой шаг
    void doStep();
};

#endif
