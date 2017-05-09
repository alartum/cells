#include <chrono>
#include <thread>
#include "field.hpp"
//#define DEBUG
#include "../debug.h"

Field::Field (sf::Vector2u sizeInTiles, sf::Vector2u sizeInPixels) :
    sf::RenderWindow(sf::VideoMode(sizeInPixels.x, sizeInPixels.y), "Field"),
    mTileSize    (32, 32),
    mMap         (sizeInTiles.x, sizeInTiles.y),
    mAnimationTime (8),
    mFrameDelay (200),
    mMaxFPS(60)
{
    setActive(false);
    setFramerateLimit(mMaxFPS);
    setTilePositions();
}

Field::~Field() {
    
}

 void Field::setTilePositions(){
     for (unsigned i = 0; i < mMap.getHeight(); i++)
         for (unsigned j = 0; j < mMap.getWidth(); j++) {
             mMap.at(i, j).setPosition(mTileSize.x * j, mTileSize.y * i);
             //LOG("POS = (%f, %f)", mMap.at(i, j).getPosition().x, mMap.at(i, j).getPosition().y);
         }
 }

void Field::fitView(){
    sf::Vector2u mapSize = getMapSize();
    LOG("Tile size: (%u, %u)", mTileSize.x, mTileSize.y);
    LOG("Map size: (%u, %u)", mapSize.x, mapSize.y);
    LOG("Real size: (%u, %u)", getSize().x, getSize().y);
    sf::Vector2u realSize(mTileSize.x * mapSize.y, mTileSize.y * mapSize.x);
    // Proportions of the real size of the map
    if (realSize.x == 0 || realSize.y == 0)
        return;
    float prop_x = (float)mapSize.x / mapSize.y;
    float prop_y = (float)mapSize.y / mapSize.x;

    LOG("prop_x, prop_y: (%f, %f)", prop_x, prop_y);
    sf::Vector2u window_size = getSize();
    sf::Vector2u x_bestFit(window_size.x, window_size.x * prop_x);
    sf::Vector2u y_bestFit(window_size.y * prop_y, window_size.y);
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
    mMap.setSize(size.x, size.y);
}

sf::Vector2u Field::getTileSize() const{
    return mTileSize;
}

void Field::setTileSize(sf::Vector2u size){
    mTileSize = size;

}

sf::Vector2u Field::getMapSize() const{
    return sf::Vector2u(mMap.getHeight(), mMap.getWidth());
}

void Field::loadEntityTextures(){
    for (auto& ent: mEntities){
        LOG("Entity ID: %d", ent.getTypeID());
        ent.setModelManager(mModelManager);
        ent.loadModel();
        ent.setState(STATE_IDLE | DIR_UP);
        ent.initFrame();
    }
}

void Field::loadTileTextures(){
    for (auto& tile: mMap){
        tile.setModelManager(mModelManager);
        tile.loadModel();
        tile.initState();
        tile.initFrame();
    }
    fancyEdges();
}

void Field::setModelManager (const std::shared_ptr<const ModelManager>& modelManager_ptr) {
    mModelManager = modelManager_ptr;
    mTileSize = mModelManager->getTileSize();
    mAnimationTime = mModelManager->getAnimationTime();
    mFrameDelay = mModelManager->getFrameDelay();
    mMaxFPS = mModelManager->getMaxFPS();
    setFramerateLimit(mMaxFPS);
}

//! TODO matrix coords -> absolute coords
void Field::drawEntities() {
    for (auto& ent: mEntities){
        //LOG("Entity ID: %d", ent.getTypeID());
        //LOG("Entity pos: %f, %f", ent.getPosition().x, ent.getPosition().y);
        //ent.nextFrame();
        draw(ent);
    }
}

void Field::drawTiles() {
    //LOG("ITERATION");
    for (auto& tile: mMap){
        draw(tile);
    }
}

void Field::nextFrame() {
    for (auto& ent: mEntities) {
        ent.nextFrame();
    }
    for (auto& tile: mMap){
        tile.nextFrame();
    }
}

void Field::generateTiles(std::function< void(Matrix< Tile >&) > generatorMap) {
    generatorMap(mMap);
}

void Field::generateEntities(std::function< void(Matrix< Tile >&, std::vector< Entity >&) > generateEntities) {
    generateEntities(mMap, mEntities);
    for (auto& ent: mEntities){
        ent.calcSpritePosition(mTileSize, 0, 1);
    }
    #if defined(DEBUG)
        for (auto& ent: mEntities) {
            LOG("POS=(%lg, %lg)", ent.getPosition().x, ent.getPosition().y);
        }
    #endif
}


void Field::doStep(std::function< void(Matrix< Tile >&, std::vector< Entity >&) > do_step) {
    do_step(mMap, mEntities);
}

void Field::syncronize() {
    for (auto& ent: mEntities) {
        ent.updateRoute();
        ent.calcSpritePosition(mTileSize, 0, 1);
    }
    
}

void Field::calcSpritePosition ( double time, double stepCount ) {
    for (auto& ent: mEntities) {
        ent.calcSpritePosition(mTileSize, time, stepCount);
    }
}

void Field::setAnimationTime(int animation_time){
    mAnimationTime = animation_time;
}

int Field::getAnimationTime() const{
    return mAnimationTime;
}

void Field::showAnimation(){
    /*
    std::chrono::time_point<std::chrono::system_clock> before =
        std::chrono::system_clock::now();
*/
    for (int i = 0; i < mAnimationTime; i++) {
        calcSpritePosition(i, mAnimationTime-1);
        clear();
        drawTiles();
        drawEntities();
        display();
        nextFrame();
        if (mFrameDelay != 0){
            std::this_thread::sleep_for(std::chrono::milliseconds(mFrameDelay));
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
    // Load file without execute
    sol::load_result config_script = config.load_file(config_file);
    if (!config_script.valid()){
        PERROR("Can't load config file: %s", config_file.c_str());
        return;
    }
    // Execute under protection
    sol::protected_function_result config_result = config_script();
    if (!config_result.valid()){
        PERROR("Wrong config file format: %s", config_file.c_str());
        return;
    }
    sol::table field_size;
    LOAD_VAR(field_size, config);
    unsigned height, width;
    LOAD_VAR(height, field_size);
    LOAD_VAR(width, field_size);
    sf::Vector2u f_size(width, height);
    mMap.setSize(f_size.y, f_size.x);

    sol::table window_size;
    LOAD_VAR(window_size, config);
    LOAD_VAR(height, window_size);
    LOAD_VAR(width, window_size);
    sf::Vector2u w_size(width, height);
    setSize(w_size);
}

#define TEST_WATER(y, x) (mMap.at(y, x).getTypeID() & TILE_WATER_ID)
int Field::getEdgeType(unsigned y, unsigned x){
    int edgeType = 0;
    int maxX = mMap.getWidth() -1;
    int maxY = mMap.getHeight()-1;
    if (y != 0 && TEST_WATER(y-1, x)) edgeType |= DIR_UP;
    if (y != maxY && TEST_WATER(y+1, x)) edgeType |= DIR_DOWN;
    if (x != 0 && TEST_WATER(y, x-1)) edgeType |= DIR_LEFT;
    if (x != maxX && TEST_WATER(y, x+1)) edgeType |= DIR_RIGHT;\
    if (edgeType == 0){
        if (y != 0 && x != 0 && TEST_WATER(y-1, x-1)) edgeType |= DIR_UP | DIR_LEFT | DIR_ADD;
        if (y != maxY && x != 0 && TEST_WATER(y+1, x-1)) edgeType |= DIR_DOWN | DIR_LEFT | DIR_ADD;
        if (y != 0 && x != maxX && TEST_WATER(y-1, x+1)) edgeType |= DIR_UP | DIR_RIGHT | DIR_ADD;
        if (y != maxX && x != maxY && TEST_WATER(y+1, x+1)) edgeType |= DIR_DOWN | DIR_RIGHT | DIR_ADD;
    }
    if (edgeType == 0)
        return DIR_ADD;
    return edgeType;
}
#undef TEST_WATER

void Field::fancyEdges(){
    for (unsigned y = 0; y < mMap.getHeight(); y++)
        for (unsigned x = 0; x < mMap.getWidth(); x++) {
            Tile& tile = mMap.at(y, x);
            if (tile.getTypeID() & TILE_GRASS_ID){
                tile.setState(getEdgeType(y, x));
            }
        }
}
