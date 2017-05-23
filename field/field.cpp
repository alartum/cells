#include <chrono>
#include <thread>
#include "field.hpp"
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
    max_FPS_(60)
{
    setFixedSize(QSize(sizeInPixels.x, sizeInPixels.y));
    timer_.setInterval(1000);
    connect(&timer_, SIGNAL(timeout()), this, SLOT(proceed()));
    setFramerateLimit(max_FPS_);
    setTilePositions();
}

void Field::onInit(){
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
    LOG("Tile size: (%u, %u)", tile_size_.x, tile_size_.y);
    LOG("Map size: (%u, %u)", map_.getWidth(), map_.getHeight());
    LOG("Real size: (%u, %u)", size().width(), size().height());
    sf::Vector2u map_pix_size(map_.getWidth() * tile_size_.x,
                            map_.getHeight() * tile_size_.y);
    // Proportions of the real size of the map
    if (map_pix_size.x == 0 || map_pix_size.y == 0)
        return;
    float height_div_width = (float)size().height() / size().width();
    float width_div_height = (float)size().width() / size().height();

    LOG("prop_x, prop_y: (%f, %f)", height_div_width, width_div_height);
    sf::Vector2u x_bestFit(map_pix_size.x, map_pix_size.x * height_div_width);
    sf::Vector2u y_bestFit(map_pix_size.y * width_div_height, map_pix_size.y);
    LOG("Map px size: (%u, %u)", map_pix_size.x, map_pix_size.y);
    LOG("X best fit: (%u, %u)", x_bestFit.x, x_bestFit.y);
    LOG("Y best fit: (%u, %u)", y_bestFit.x, y_bestFit.y);

    sf::View field_view;
    if (x_bestFit.y <= map_pix_size.y)
        field_view.reset(sf::FloatRect(0, 0, x_bestFit.x, x_bestFit.y));
    else
        field_view.reset(sf::FloatRect(0, 0, y_bestFit.x, y_bestFit.y));
    field_view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    setSize(sf::Vector2u(size().width(), size().height()));
    VAR_LOG(getSize().x);
    VAR_LOG(getSize().y);
    // Use default viewport
    setView(field_view);
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

void Field::generateTiles() {
    generate_map_(map_);

}

void Field::generateEntities() {
    generate_entities_(map_, entities_);
    for (auto& ent: entities_){
        ent.calcSpritePosition(tile_size_, 0, 1);
    }
    /*
        for (auto& ent: mEntities) {
            LOG("Entity (%lg, %lg)", ent.getPosition().x, ent.getPosition().y);
        }
    */
}


void Field::doStep() {
    do_step_(map_, entities_);
	calcStatistics();
	
	for ( std::map< int, int >::iterator it = statistics_.begin(); it != statistics_.end(); it++)
		std::cout << it->first << "-" << it->second << "   ";
	std::cout << std::endl;
	
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
    calcSpritePosition(animation_frame_, animation_time_-1);
    clear();
    drawTiles();
    drawEntities();
    display();
    nextFrame();

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

    fitView();
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
        showAnimation();
        animation_frame_++;
    }
    else{
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

void Field::calcStatistics() {
	statistics_.clear();
	for ( auto & iter: entities_ )
		statistics_[iter.getID()] += 1;
}
