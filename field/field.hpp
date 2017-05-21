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

public:
    friend class MapDump;
    sf::Vector2u                        tile_size_;
    // Objects on the field
    std::vector< Entity >               entities_;
    
    Matrix<Tile>                        map_;
    // Number of ticks between the field updates
    // The animation frames are inserted uniformly
    size_t                              animation_time_;
    // The amount of time between frames
    size_t                              frame_delay_;
    size_t                              max_FPS_;

    std::shared_ptr<const ModelManager> model_manager_;

    void setTilePositions();
    void fancyEdges();
    int getEdgeType(unsigned y, unsigned x);
public:    
    Field(sf::Vector2u sizeInTiles  = sf::Vector2u(1, 1),
          sf::Vector2u sizeInPixels = sf::Vector2u(600,600));
    
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
    void setModelManager (const std::shared_ptr<const ModelManager>& model_manager_ptr);

    // Отрисовать только объекты
    void drawEntities();

    // Отрисовать только тайлы
    void drawTiles();
        
    // Функция генерации тайлов поля
    void generateTiles    (std::function< void(Matrix< Tile >&) > generator_map);
    
    // Функция генерации объектов на поле
    void generateEntities (std::function< void(Matrix< Tile >&, std::vector< Entity >&) > generate_entities);
    
    // Функция пересчета состояния поля на один игровой шаг
    void doStep           (std::function< void(Matrix< Tile >&, std::vector< Entity >&) > do_step);

    void syncronize();
    
    void calcSpritePosition ( double time, double step_count );
    
    void nextFrame();

    void setAnimationTime(int animation_time);
    int getAnimationTime() const;

    void showAnimation();
    void loadConfig(const std::string config_file);
};

#endif
