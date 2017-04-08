#include "gameitem.hpp"

GameItem::GameItem(const std::shared_ptr<const ModelManager> &modelManagerPtr,
                   int typeID,
                   const sf::Vector2f &position,
                   unsigned state) :
    mModelManager(modelManagerPtr),
    mTypeID(typeID),
    Item(mModelManager->getModel(mTypeID), position, state)
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
    setModel(mModelManager->getModel(mTypeID));
}
