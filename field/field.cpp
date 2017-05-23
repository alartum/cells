#include <chrono>
#include <thread>
#include "field.hpp"
#include <algorithm>
#define DEBUG
#include "../debug.h"

Field::Field (QWidget* parent,
              const QPoint& pos,
              const sf::Vector2u& sizeInTiles,
              const sf::Vector2u& sizeInPixels) :
    QSFMLWidget(parent, pos, QSize(sizeInPixels.x, sizeInPixels.y)),
    tile_size_    (32, 32),
    map_         (sizeInTiles.x, sizeInTiles.y),
    animation_time_ (8),
    animation_frame_(0),
    max_FPS_(60),
    moving_(false),
    last_point_(0, 0),
    minimap_shown_(true)
{
    setFixedSize(QSize(sizeInPixels.x, sizeInPixels.y));
    setSize(sizeInPixels);
    field_view_.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    if (sizeInPixels.x != 0 && sizeInPixels.y != 0)
        view_aspect_ratio_ = static_cast<double>(sizeInPixels.x) / sizeInPixels.y;
    timer_.setInterval(0);
    connect(&timer_, SIGNAL(timeout()), this, SLOT(proceed()));
    setFramerateLimit(max_FPS_);
    setTilePositions();
}

Field::~Field() {
}

std::function<void (Matrix<Tile> &)> Field::getGenerateMap() const
{
    return generate_map_;
}

void Field::setGenerateMap(const std::function<void (Matrix<Tile> &)> &generate_map)
{
    generate_map_ = generate_map;
}

std::function<void (Matrix<Tile> &, std::vector<Entity> &)> Field::getGenerateEntities() const
{
    return generate_entities_;
}

void Field::setGenerateEntities(const std::function<void (Matrix<Tile> &, std::vector<Entity> &)> &generate_entities)
{
    generate_entities_ = generate_entities;
}

std::function<void (Matrix<Tile> &, std::vector<Entity> &)> Field::getDoStep() const
{
    return do_step_;
}

void Field::setDoStep(const std::function<void (Matrix<Tile> &, std::vector<Entity> &)> &do_step)
{
    do_step_ = do_step;
}

void Field::setTilePositions(){
    for (unsigned i = 0; i < map_.getHeight(); i++)
        for (unsigned j = 0; j < map_.getWidth(); j++)
            map_.at(i, j).setPosition(tile_size_.x * j, tile_size_.y * i);
 }

void Field::updateValidRect(){
    valid_rect_.left   = field_view_.getSize().x / 2;
    valid_rect_.top    = field_view_.getSize().y / 2;
    valid_rect_.width  = map_.getWidth() * tile_size_.x
                         - field_view_.getSize().x;
    valid_rect_.height = map_.getHeight() * tile_size_.y
                         - field_view_.getSize().y;
}

void Field::zoomIn(){
    // Normalize
    field_view_.setSize(view_aspect_ratio_, 1.f);
    // Get multiplication coefficient
    float x_zoom = tile_size_.x / view_aspect_ratio_;
    float y_zoom = tile_size_.y;

    // Fit the field
    field_view_.zoom(std::max(x_zoom, y_zoom));
}

void Field::zoomOut(){
    // Normalize
    field_view_.setSize(view_aspect_ratio_, 1.f);
    // Get multiplication coefficient
    float x_zoom = map_.getWidth() * tile_size_.x / view_aspect_ratio_;
    float y_zoom = map_.getHeight() * tile_size_.y;

    // Fit the field
    field_view_.zoom(std::min(x_zoom, y_zoom));
}

void Field::setMapSize(sf::Vector2u size){
    map_.setSize(size.x, size.y);
}

sf::Vector2u Field::getTileSize() const{
    return tile_size_;
}

void Field::setTileSize(sf::Vector2u size){
    tile_size_ = size;

}

sf::Vector2u Field::getMapSize() const{
    return sf::Vector2u(map_.getHeight(), map_.getWidth());
}

void Field::loadEntityTextures(){
    for (auto& ent: entities_){
        ent.setModelManager(model_manager_);
        ent.loadModel();
        ent.setState(STATE_IDLE | DIR_UP);
        ent.initFrame();
    }
}

void Field::loadTileTextures(){
    for (auto& tile: map_){
        tile.setModelManager(model_manager_);
        tile.loadModel();
        tile.initState();
        tile.initFrame();
    }

    fancyEdges();
}

void Field::setModelManager (const std::shared_ptr<const ModelManager>& model_manager_ptr) {
    model_manager_ = model_manager_ptr;
    tile_size_ = model_manager_->getTileSize();
    animation_time_ = model_manager_->getAnimationTime();
    timer_.setInterval (model_manager_->getFrameDelay());
    max_FPS_ = model_manager_->getMaxFPS();
    setFramerateLimit (max_FPS_);
}

void Field::drawEntities() {
    for (auto& ent: entities_){
        draw(ent);
    }
}

void Field::drawTiles() {
    for (auto& tile: map_)
        draw(tile);
}

void Field::nextFrame() {
    for (auto& ent: entities_) {
        ent.nextFrame();
    }
    for (auto& tile: map_){
        tile.nextFrame();
    }
}

void Field::generateTiles() {
    generate_map_(map_);

}

void Field::generateEntities() {
    generate_entities_(map_, entities_);
    for (auto& ent: entities_)
        ent.calcSpritePosition(tile_size_, 0, 1);
}


void Field::doStep() {
    do_step_(map_, entities_);
}

void Field::syncronize() {
    for (auto& ent: entities_) {
        ent.updateRoute();
        ent.calcSpritePosition(tile_size_, 0, 1);
    }
}

void Field::calcSpritePosition (double time, double step_count ) {
    for (auto& ent: entities_) {
        ent.calcSpritePosition(tile_size_, time, step_count);
    }
}

void Field::setAnimationTime(int animation_time){
    animation_time_ = animation_time;
}

int Field::getAnimationTime() const{
    return animation_time_;
}

void Field::drawAnimation(){
    /*
    std::chrono::time_point<std::chrono::system_clock> before =
        std::chrono::system_clock::now();
*/
    // Prepare to draw the field
    setView(field_view_);
    calcSpritePosition(animation_frame_, animation_time_-1);
    drawTiles();
    drawEntities();

    /*std::chrono::time_point<std::chrono::system_clock> after =
        std::chrono::system_clock::now();
    auto duration = after.time_since_epoch() - before.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    LOG("FPS: %d", 1000 / (millis / mAnimationTime));
    */
}

#define LOAD_VAR(var, from) \
{\
    auto obj = from[#var];\
    if (obj.valid()){\
        var = obj;\
    }\
    else{\
        PERROR("Can't find \"%s\" in %s", #var, #from);\
        return;\
    }\
}

void Field::loadConfig(const std::string config_file){
    sol::state config;
    LOG("Loading config file: %s", config_file.c_str());
    // Load and execute script
    // May throw!
    config.script_file(config_file, sol::default_on_error);

    sol::table field_size;
    LOAD_VAR(field_size, config);
    unsigned height, width;
    LOAD_VAR(height, field_size);
    LOAD_VAR(width, field_size);
    map_.setSize(height, width);
    setTilePositions();

    sol::table window_size;
    LOAD_VAR(window_size, config);
    LOAD_VAR(height, window_size);
    LOAD_VAR(width, window_size);
    setFixedSize(width, height);
    setSize(sf::Vector2u(width, height));
    validateView();
}

#define TEST_WATER(y, x) (map_.at(y, x).getID() & TILE_WATER_ID)
int Field::getEdgeType(unsigned y, unsigned x){
    int edgeType = 0;
    unsigned maxX = map_.getWidth() -1;
    unsigned maxY = map_.getHeight()-1;
    if (y != 0 && TEST_WATER(y-1, x)) edgeType |= DIR_UP;
    if (y != maxY && TEST_WATER(y+1, x)) edgeType |= DIR_DOWN;
    if (x != 0 && TEST_WATER(y, x-1)) edgeType |= DIR_LEFT;
    if (x != maxX && TEST_WATER(y, x+1)) edgeType |= DIR_RIGHT;\
    if (edgeType == 0){
        if (y != 0 && x != 0 && TEST_WATER(y-1, x-1)) edgeType |= DIR_UP | DIR_LEFT | DIR_ADD;
        if (y != maxY && x != 0 && TEST_WATER(y+1, x-1)) edgeType |= DIR_DOWN | DIR_LEFT | DIR_ADD;
        if (y != 0 && x != maxX && TEST_WATER(y-1, x+1)) edgeType |= DIR_UP | DIR_RIGHT | DIR_ADD;
        if (y != maxY && x != maxX && TEST_WATER(y+1, x+1)) edgeType |= DIR_DOWN | DIR_RIGHT | DIR_ADD;
    }
    if (edgeType == 0)
        return DIR_ADD;
    return edgeType;
}
#undef TEST_WATER

void Field::fancyEdges(){
    for (unsigned y = 0; y < map_.getHeight(); y++)
        for (unsigned x = 0; x < map_.getWidth(); x++) {
            Tile& tile = map_.at(y, x);
            if (tile.getID() & TILE_GRASS_ID){
                tile.setState(getEdgeType(y, x));
            }
        }
}

void Field::proceed(){
    if (animation_frame_ < animation_time_){
        clear();
        drawAnimation();
        drawMinimap();
        display();
        nextFrame();
        animation_frame_++;
    }
    else{
        drawMinimap();
        display();
        doStep();
        syncronize();
        animation_frame_ = 0;
    }
}

void Field::start(){
    timer_.start();
}

void Field::stop(){
    timer_.stop();
}

void Field::keyPressEvent(QKeyEvent * event){
    switch (event->key())
    {
    case Qt::Key_M:
        minimap_shown_ = !minimap_shown_;
        break;
    }
}

void Field::moveView(const QPoint &from, const QPoint &to){
    // Map projections
    sf::Vector2f from_map = mapPixelToCoords(sf::Vector2i(from.x(), from.y()),
                                            field_view_);
    sf::Vector2f to_map = mapPixelToCoords(sf::Vector2i(to.x(), to.y()),
                                            field_view_);
    field_view_.move(from_map - to_map);
    validateViewCenter();
}

void Field::validateViewCenter(){
    sf::Vector2f center = field_view_.getCenter();

    center.x = std::max(center.x, valid_rect_.left);
    center.x = std::min(center.x, valid_rect_.left + valid_rect_.width);

    center.y = std::max(center.y, valid_rect_.top);
    center.y = std::min(center.y, valid_rect_.top + valid_rect_.height);

    field_view_.setCenter(center);
}

void Field::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        last_point_ = event->pos();
        moving_ = true;
    }
}

void Field::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && moving_){
        moveView(last_point_, event->pos());
        last_point_ = event->pos();
    }
}

void Field::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && moving_) {
        moveView(last_point_, event->pos());
        moving_ = false;
    }
}

void Field::validateViewSize(){
    sf::Vector2f size = field_view_.getSize();
    if (size.x        < static_cast<float>(tile_size_.x)
            || size.y < static_cast<float>(tile_size_.y))
        zoomIn();
    else if (size.x    > static_cast<float>(map_.getWidth()  * tile_size_.x)
             || size.y > static_cast<float>(map_.getHeight() * tile_size_.y))
        zoomOut();
}

#define ZOOM_SENSITIVITY 500
void Field::wheelEvent(QWheelEvent* event){
    field_view_.zoom(1 - static_cast<float>(event->delta()) / ZOOM_SENSITIVITY);
    validateView();
}

void Field::validateView(){
    validateViewSize();
    updateValidRect();
    validateViewCenter();
}

#include <SFML/Graphics/RectangleShape.hpp>

template<typename T>
void zoom(sf::Vector2<T>& v, float factor){
    v.x *= factor;
    v.y *= factor;
}

void Field::drawMinimap(){
    if (minimap_shown_){
        float map_aspect_ratio_ = static_cast<float>(map_.getWidth()) / map_.getHeight();
        sf::Vector2f viewport(map_aspect_ratio_, 1.f);
        sf::Vector2f minimap_rect(0.25f, 0.25f);
        sf::Vector2f offset(0.005f, 0.005f);
        zoom(viewport, std::min(minimap_rect.x / map_aspect_ratio_,
                                minimap_rect.y / 1.f));
        minimap_.setViewport(sf::FloatRect(1-viewport.x - 2*offset.x,
                                           0,
                                           viewport.x+2*offset.x,
                                           viewport.y+2*offset.y));
        minimap_.reset(sf::FloatRect(0, 0, 1, 1));
        // Prepare to draw the map
        setView(minimap_);

        // Draw a rectangle behind the minimap
        sf::RectangleShape miniback;
        miniback.setPosition(0,0);
        miniback.setSize(sf::Vector2f(1, 1));
        miniback.setFillColor(sf::Color::Black);

        draw(miniback);
        minimap_.setViewport(sf::FloatRect(1-viewport.x - offset.x,
                                           offset.y,
                                           viewport.x,
                                           viewport.y));
        minimap_.reset(sf::FloatRect(0, 0, map_.getWidth()*tile_size_.x,
                                     map_.getHeight()*tile_size_.y));
        // Prepare to draw the map
        setView(minimap_);
        drawTiles();
        sf::RectangleShape current_view; // We want to draw a rectangle behind the minimap
        current_view.setPosition(field_view_.getCenter().x - field_view_.getSize().x/2,
                             field_view_.getCenter().y - field_view_.getSize().y/2);
        current_view.setSize(field_view_.getSize());
        current_view.setFillColor(sf::Color(255, 255, 255, 80));
        draw(current_view);
    }
}
