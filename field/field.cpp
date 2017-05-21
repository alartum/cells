#include <chrono>
#include <thread>
#include "field.hpp"
#define DEBUG
#include "../debug.h"

Field::Field (sf::Vector2u sizeInTiles, sf::Vector2u sizeInPixels) :
    sf::RenderWindow(sf::VideoMode(sizeInPixels.x, sizeInPixels.y), "Field"),
    tile_size_    (32, 32),
    map_         (sizeInTiles.x, sizeInTiles.y),
    animation_time_ (8),
    frame_delay_ (200),
    max_FPS_(60)
{
    setActive(false);
    setFramerateLimit(max_FPS_);
    setTilePositions();
}

Field::~Field() {
    
}

 void Field::setTilePositions(){
     for (unsigned i = 0; i < map_.getHeight(); i++)
         for (unsigned j = 0; j < map_.getWidth(); j++) {
             map_.at(i, j).setPosition(tile_size_.x * j, tile_size_.y * i);
             //LOG("POS = (%f, %f)", mMap.at(i, j).getPosition().x, mMap.at(i, j).getPosition().y);
         }
 }

void Field::fitView(){
    sf::Vector2u mapSize(map_.getHeight(), map_.getWidth());
    LOG("Tile size: (%u, %u)", tile_size_.x, tile_size_.y);
    LOG("Map size: (%u, %u)", mapSize.x, mapSize.y);
    LOG("Real size: (%u, %u)", getSize().x, getSize().y);
    sf::Vector2u realSize(tile_size_.x * mapSize.y, tile_size_.y * mapSize.x);
    // Proportions of the real size of the map
    if (realSize.x == 0 || realSize.y == 0)
        return;
    float height_div_width = (float)mapSize.x / mapSize.y;
    float width_div_height = (float)mapSize.y / mapSize.x;

    LOG("prop_x, prop_y: (%f, %f)", height_div_width, width_div_height);
    sf::Vector2u window_size = getSize();
    sf::Vector2u x_bestFit(window_size.x, window_size.x * height_div_width);
    sf::Vector2u y_bestFit(window_size.y * width_div_height, window_size.y);
    LOG("Map px size: (%u, %u)", realSize.x, realSize.y);
    LOG("X best fit: (%u, %u)", x_bestFit.x, x_bestFit.y);
    LOG("Y best fit: (%u, %u)", y_bestFit.x, y_bestFit.y);
    if (x_bestFit.y <= window_size.y)
        setSize(x_bestFit);
    else
        setSize(y_bestFit);

    sf::View fieldView(sf::FloatRect(0, 0, realSize.x, realSize.y));
    // Use default viewport
    setView(fieldView);
    LOG("New size: (%u, %u)", getSize().x, getSize().y);
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
        //LOG("Entity ID: %d", ent.getTypeID());
        ent.setModelManager(model_manager_);
        ent.loadModel();
        ent.setState(STATE_IDLE | DIR_UP);
        ent.initFrame();
        /*LOG("Info: [%s](%u, %u) --> (%u, %u)", ent.getModel()->getName().c_str(),
            ent.getTileFrom().x, ent.getTileFrom().y,
            ent.getTileTo().x, ent.getTileTo().y);
            */
    }
}

void Field::loadTileTextures(){
    for (auto& tile: map_){
        tile.setModelManager(model_manager_);
        tile.loadModel();
        tile.initState();
        tile.initFrame();
    }
    for (unsigned i = 0; i < map_.getHeight(); i ++){
        for (unsigned j = 0; j < map_.getWidth(); j ++){
            Tile& tile = map_.at(i, j);
        }
    }
    fancyEdges();
}

void Field::setModelManager (const std::shared_ptr<const ModelManager>& model_manager_ptr) {
    model_manager_ = model_manager_ptr;
    tile_size_ = model_manager_->getTileSize();
    animation_time_ = model_manager_->getAnimationTime();
    frame_delay_ = model_manager_->getFrameDelay();
    max_FPS_ = model_manager_->getMaxFPS();
    setFramerateLimit(max_FPS_);
}

void Field::drawEntities() {
    for (auto& ent: entities_){
        //LOG("Entity ID: %d", ent.getTypeID());
        //LOG("Entity pos: %f, %f", ent.getPosition().x, ent.getPosition().y);
        //ent.nextFrame();
        draw(ent);
    }
}

void Field::drawTiles() {
    for (auto& tile: map_){
        draw(tile);
    }
    
    /*for (unsigned i = 0; i < mMap.getHeight(); i ++){
        for (unsigned j = 0; j < mMap.getWidth(); j ++){
            Tile& tile = mMap.at(i, j);
            //LOG("Info: (%u, %u)[%s]{0x%x : 0x%x}", i, j, tile.getModel()->getName().c_str(),
            //+tile.getState(), tile.getFrame());
            //LOG("      (%f, %f)", tile.getPosition().x, tile.getPosition().y);
            //LOG("      {(%d, %d), (%d, %d)}", tile.getTextureRect().left, tile.getTextureRect().top,
            //    tile.getTextureRect().width, tile.getTextureRect().height);
            //LOG("      {%p}", tile.getTexture());
            draw(tile);
        }
    }
    */
    
}

void Field::nextFrame() {
    for (auto& ent: entities_) {
        ent.nextFrame();
    }
    for (auto& tile: map_){
        tile.nextFrame();
    }
}

void Field::generateTiles(std::function< void(Matrix< Tile >&) > generator_map) {
    generator_map(map_);

}

void Field::generateEntities(std::function< void(Matrix< Tile >&, std::vector< Entity >&) > generate_entities) {
    generate_entities(map_, entities_);
    for (auto& ent: entities_){
        ent.calcSpritePosition(tile_size_, 0, 1);
    }
    /*
        for (auto& ent: mEntities) {
            LOG("Entity (%lg, %lg)", ent.getPosition().x, ent.getPosition().y);
        }
    */
}


void Field::doStep(std::function< void(Matrix< Tile >&, std::vector< Entity >&) > do_step) {
    do_step(map_, entities_);
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

void Field::showAnimation(){
    /*
    std::chrono::time_point<std::chrono::system_clock> before =
        std::chrono::system_clock::now();
*/
    for (int i = 0; i < animation_time_; i++) {
        calcSpritePosition(i, animation_time_-1);
        clear();
        drawTiles();
        drawEntities();
        display();
        nextFrame();
        if (frame_delay_ != 0){
            std::this_thread::sleep_for(std::chrono::milliseconds(frame_delay_));
        }
    }
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
    sf::Vector2u w_size(width, height);
    setSize(w_size);
}

#define TEST_WATER(y, x) (map_.at(y, x).getID() & TILE_WATER_ID)
int Field::getEdgeType(unsigned y, unsigned x){
    int edgeType = 0;
    int maxX = map_.getWidth() -1;
    int maxY = map_.getHeight()-1;
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
