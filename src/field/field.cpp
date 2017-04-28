#include "field.hpp"
#define DEBUG
#include "../debug.h"

Field::Field (sf::Vector2u sizeInTiles, sf::Vector2u sizeInPixels, sf::Vector2u tileSize) :
    sf::RenderWindow(sf::VideoMode(sizeInPixels.x, sizeInPixels.y), "Field"),
    mTileSize    (tileSize),
    mMap         (sizeInTiles.x, sizeInTiles.y)
{
    setActive(false);
    setFramerateLimit(60);
    setTilePositions();
//    fitView();
}

Field::~Field() {
    
}

 void Field::setTilePositions(){
     for (unsigned i = 0; i < mMap.getHeight(); i++)
         for (unsigned j = 0; j < mMap.getWidth(); j++) {
             mMap.at(i, j).setPosition(mTileSize.x * j, mTileSize.y * i);
             LOG("POS = (%f, %f)", mMap.at(i, j).getPosition().x, mMap.at(i, j).getPosition().y);
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
        ent.setModelManager(mModelManager);
        ent.loadModel();
        if (ent.getTypeID() == OBJECT_GRASS_EATING_ID){
            ent.setState(rand() % 4);
            ent.setFrame(rand() % 4);
        }
    }
}

void Field::loadTileTextures(){
    for (unsigned i = 0; i < mMap.getHeight(); i++){
        for (unsigned j = 0; j < mMap.getWidth(); j++){
//            LOG("POS = (%f, %f)", mMap.at(i, j).getPosition().x, mMap.at(i, j).getPosition().y);
            mMap.at(i, j).setModelManager(mModelManager);
            mMap.at(i, j).loadModel();
        }
    }
}

void Field::setModelManager (const std::shared_ptr<const ModelManager>& modelManager_ptr) {
    mModelManager = modelManager_ptr;
//    setTileModelManager();
}

//! TODO matrix coords -> absolute coords
void Field::drawEntities() {
    for (auto& ent: mEntities){
        //LOG("Entity ID: %d", ent.getTypeID());
       // LOG("Entity pos: %f, %f", ent.getPosition().x, ent.getPosition().y);
        ent.nextFrame();
        draw(ent);
    }
}

void Field::drawTiles() {
    //LOG("ITERATION");
    for (unsigned i = 0; i < mMap.getHeight(); i++)
        for (unsigned j = 0; j < mMap.getWidth(); j++) {
            Tile& curr_item = mMap.at(i, j);
            //LOG("[%u, %u]", i, j);
            //LOG("ID = %d", curr_item.getTypeID());
            //LOG("POS = (%f, %f)", curr_item.getPosition().x, curr_item.getPosition().y);
            curr_item.nextFrame();
            draw(curr_item);
        }
}

void Field::generateTiles(std::function< void(Matrix< Tile >&) > generatorMap) {
    generatorMap(mMap);
}

//! TODO coords
void Field::generateEntities(std::function< void(Matrix< Tile >&, std::vector< Entity >&) > generateEntities) {
    generateEntities(mMap, mEntities);
    for (auto& ent: mEntities){
        sf::Vector2f ent_pos(ent.getPosition().y * mTileSize.x, ent.getPosition().x * mTileSize.y);
        ent.setPosition(ent_pos);
    }
}


void Field::doStep() {
}

