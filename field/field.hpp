#ifndef HEADER_FIELD_HPP_INCLUDED
#define HEADER_FIELD_HPP_INCLUDED

#include <QTimer>

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
#include "../qsfmlwidget/qsfmlwidget.hpp"

class Field : public QSFMLWidget
{
    Q_OBJECT
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
    QTimer                              timer_;
    size_t                              max_FPS_;

    std::shared_ptr<const ModelManager> model_manager_;

    std::function< void(Matrix< Tile >&) > generate_map_;
    std::function< void(Matrix< Tile >&, std::vector< Entity >&) > generate_entities_;
    std::function< void(Matrix< Tile >&, std::vector< Entity >&) > do_step_;

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
    void generateTiles    ();
    
    // Функция генерации объектов на поле
    void generateEntities ();
    
    // Функция пересчета состояния поля на один игровой шаг
    void doStep           ();

    void syncronize();
    
    void calcSpritePosition ( double time, double step_count );
    
    void nextFrame();

    void setAnimationTime(int animation_time);
    int getAnimationTime() const;

    void showAnimation();
    void loadConfig(const std::string config_file);

public slots:
    // Do step and animation
    void proceed();
    // Begin and stop the simulation process
    void start();
    void stop();
};

#endif
