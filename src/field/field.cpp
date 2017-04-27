#include "field.hpp"
#include "../debug.h"

Field::Field (  sf::RenderWindow&       Window,
                sf::Vector2u&           sizeTiles,
                unsigned                tileSize
             ) :
                mWindow         (Window),
                mSizeTiles      (sizeTiles),
                mTileSize       (tileSize),
                mMap            (sizeTiles.x, sizeTiles.y, Tile(1)) 
            {            
    for (unsigned i = 0; i < sizeTiles.x; i++)
        for (unsigned j = 0; j < sizeTiles.y; j++) {
            mMap.at(i, j).setPosition(tileSize * i, tileSize * j);
        }
}

Field::~Field() {
    
}

sf::RenderWindow& Field::getWindow() {
    return mWindow;
}

unsigned int Field::getWidth() {
    return mSizeTiles.y;
}

unsigned Field::getHeight() {
    return mSizeTiles.x;
}

sf::Vector2u Field::getSize() {
    return mSizeTiles;
}

bool Field::isWindowOpen() {
    return mWindow.isOpen();
}

void Field::setActive ( bool status ) {
    mWindow.setActive( status );
}

void Field::setModelManager (const std::shared_ptr<const ModelManager>& modelManager_ptr) {
    mModelManager = modelManager_ptr;
    for (unsigned i = 0; i < mSizeTiles.x; i++)
        for (unsigned j = 0; j < mSizeTiles.y; j++) {
            mMap.at(i, j).setModelManager(mModelManager);
            mMap.at(i, j).loadModel();
        }
}

void Field::draw() {
    for (unsigned i = 0; i < mMap.getHeight(); i++)
        for (unsigned j = 0; j < mMap.getWidth(); j++) {
            Tile& currentTile = mMap.at(i, j);
            currentTile.nextFrame();
            mWindow.draw(currentTile);
        }
}

void drawObjects() {
}

void Field::drawTiles() {
    for (unsigned i = 0; i < mMap.getHeight(); i++)
        for (unsigned j = 0; j < mMap.getWidth(); j++) {
            Item& curr_item = mMap.at(i, j);
            curr_item.nextFrame();
            mWindow.draw(curr_item);
        }
}

void Field::display() {
    mWindow.display();    
}

void Field::generateTiles(std::function< void(Matrix< Tile >&) > generatorMap) {
    generatorMap(mMap);
}

void Field::generateObjects(std::function< void(Matrix< Tile >&, std::vector< Object* >&) > generatorObjects) {
    generatorObjects(mMap, mObjects);
}


void Field::doStep() {
}

