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
    //! Is the speed up really needed?
    friend void UpdateThread(Field& F);
private:
    sf::Vector2u                        mTileSize;
    // Objects on the field
    std::vector< Entity >               mEntities;
    Matrix<Tile>                        mMap;
    // Number of ticks between the field updates
    // The animation frames are inserted uniformly
    size_t                              mAnimationTime;
    // The amount of time between frames
    size_t                              mFrameDelay;
    size_t                              mMaxFPS;

    std::shared_ptr<const ModelManager> mModelManager;

    void setTilePositions();
public:    
    Field(sf::Vector2u sizeInTiles, sf::Vector2u sizeInPixels);
    
    ~Field();
    void fitView();
    // Sets model manager for every tile
    void loadTileTextures();
    // Sets model manager for every entity
    void loadEntityTextures();
    void setMapSize(sf::Vector2u size);
    sf::Vector2u getMapSize() const;
    void setTileSize(sf::Vector2u size);
    sf::Vector2u getTileSize() const;
    void setModelManager (const std::shared_ptr<const ModelManager>& modelManagerPtr);

    // Отрисовать только объекты
    void drawEntities();

    // Отрисовать только тайлы
    void drawTiles();
        
    // Функция генерации тайлов поля
    void generateTiles          (std::function< void(Matrix< Tile >&) > generatorMap);
    
    // Функция генерации объектов на поле
    void generateEntities       (std::function< void(Matrix< Tile >&, std::vector< Entity >&) > generateEntities);
    
    // Функция пересчета состояния поля на один игровой шаг
    void doStep                 (std::function< void(Matrix< Tile >&, std::vector< Entity >&) > do_step);

    void syncronize();
    
    void calcSpritePosition ( double time, double stepCount );
    
    void nextFrame();

    void setAnimationTime(int animation_time);
    int getAnimationTime() const;

    void showAnimation();
};

#endif
