#include "gameitem.hpp"
#define DEBUG
#include "../debug.h"
GameItem::GameItem( int typeID,
                    const sf::Vector2f &position,
                    unsigned state
                  ) :
    Item(position, state),
    mTypeID(typeID)
{
}

int GameItem::getTypeID() const
{
    return mTypeID;
}

void GameItem::setTypeID(int TypeID)
{
    if (TypeID == mTypeID)
        return;

    mTypeID = TypeID;
    loadModel();
    initState();
    initFrame();
}

void GameItem::setModelManager (const std::shared_ptr<const ModelManager>& modelManager_ptr)
{
    mModelManager = modelManager_ptr;
}

void GameItem::loadModel()
{
    if (mModelManager)
        setModel(mModelManager->getModel(mTypeID));
}

std::shared_ptr<const ModelManager> GameItem::getModelManager() const
{
    return mModelManager;
}

GameItem& GameItem::operator = (const GameItem& other){
    mModelManager = other.mModelManager;
    setTypeID(other.mTypeID);
    return *this;
}
