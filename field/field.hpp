#ifndef HEADER_FIELD_HPP_INCLUDED
#define HEADER_FIELD_HPP_INCLUDED

#include <QTimer>
#include <QPoint>
#include <QWidget>
#include "../qsfmlwidget/qsfmlwidget.hpp"
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <QKeyEvent>
#include <SFML/Graphics/Rect.hpp>

#include "../tile/tile.hpp"
#include "../matrix/matrix.hpp"
#include "../object/object.hpp"
#include "../generate_objects/generateobjects.hpp"
#include "../generate_map/generatemap.hpp"
#include "../do_step/dostep.hpp"
#include "../model_manager/modelmanager.hpp"
#include "../do_step/dostep.hpp"

class Field : public QSFMLWidget
{
    Q_OBJECT
private:
    friend class MapDump;
    sf::Vector2u                        tile_size_;
    // Objects on the field
    std::vector< Entity >               entities_;
    
    Matrix<Tile>                        map_;
    // Number of ticks between the field updates
    // The animation frames are inserted uniformly
    size_t                              animation_time_;
    // Current animation frame in [0, animation_time_)
    size_t                              animation_frame_;
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
    void calcSpritePosition (double time, double step_count);
    // MINIMAP INTERFACE //
    sf::View minimap_;
    bool minimap_shown_;
    // VIEW MOVING INTERFACE //
    // Aspect Ratio = Window's Width / Window's Height
    float view_aspect_ratio_;
    sf::View field_view_;
    // Are we mooving the view (left mouse button pressed)
    bool moving_;
    // The last place where the mouse was spotted
    QPoint last_point_;
    // Valid positions for the view center
    sf::FloatRect valid_rect_;
    // Sets the maximum possible view
    void zoomOut();
    // Sets the minimum possible view
    void zoomIn();
    // Moves view by given offset in WIDGET's COORDINATES if possible
    void moveView(const QPoint& from, const QPoint& to);
    // Updates if the the view is updated
    void updateValidRect();
    void validateViewCenter();
    void validateViewSize();
    void validateView();
protected:
    void keyPressEvent(QKeyEvent * event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *);
public:    
    Field(QWidget* parent = nullptr, const QPoint& pos = QPoint(),
          const sf::Vector2u& sizeInTiles = sf::Vector2u(1, 1),
          const sf::Vector2u& sizeInPixels = sf::Vector2u(600,600));
    
    ~Field();
    void toggleMinimap();
    // Sets model manager for every tile
    void loadTileTextures();
    // Sets model manager for every entity
    void loadEntityTextures();
    void drawEntities     ();
    void drawTiles        ();
    void generateTiles    ();
    void generateEntities ();
    // Функция пересчета состояния поля на один игровой шаг
    void doStep           ();
    // Save changes done by doStep
    void syncronize       ();
    void nextFrame();
    void showAnimation();
    void loadConfig(const std::string config_file);

    // SETTERS & GETTERS //
    std::function<void (Matrix<Tile> &)> getGenerateMap() const;
    void setGenerateMap(const std::function<void (Matrix<Tile> &)> &generate_map);
    std::function<void (Matrix<Tile> &, std::vector<Entity> &)> getGenerateEntities() const;
    void setGenerateEntities(const std::function<void (Matrix<Tile> &, std::vector<Entity> &)> &generate_entities);
    std::function<void (Matrix<Tile> &, std::vector<Entity> &)> getDoStep() const;
    void setDoStep(const std::function<void (Matrix<Tile> &, std::vector<Entity> &)> &do_step);
    void setMapSize(sf::Vector2u size);
    sf::Vector2u getMapSize() const;
    void setTileSize(sf::Vector2u size);
    sf::Vector2u getTileSize() const;
    void setModelManager (const std::shared_ptr<const ModelManager>& model_manager_ptr);
    void setAnimationTime(int animation_time);
    int getAnimationTime() const;

public slots:
    // Do step and animation
    void proceed();
    // Begin and stop the simulation process
    void start();
    void stop();
};

#endif
