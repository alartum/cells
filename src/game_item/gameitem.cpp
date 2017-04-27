#include "gameitem.hpp"

GameItem::GameItem(int typeID,
                    const sf::Vector2f &position,
                    unsigned state) :
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
}

void GameItem::setModelManager (const std::shared_ptr<const ModelManager>& modelManagerPtr)
{
    mModelManager = modelManagerPtr;
}

void GameItem::loadModel()
{
    LOG("[GameItem.loadModel()] mTypeID = %d", mTypeID);
    if (mModelManager)
        setModel(mModelManager->getModel(mTypeID));
}

std::shared_ptr<const ModelManager> GameItem::getModelManager() const
{
    return mModelManager;
}
