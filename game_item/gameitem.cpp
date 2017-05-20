#include "gameitem.hpp"
#define DEBUG
#include "../debug.h"
GameItem::GameItem( int typeID,
                    const sf::Vector2f &position,
                    unsigned state
                  ) :
    Item(position, state),
    ID_(typeID)
{
}

int GameItem::getID() const
{
    return ID_;
}

void GameItem::setID(int ID)
{
    if (ID == ID_)
        return;

    ID_ = ID;
    loadModel();
    initState();
    initFrame();
}

void GameItem::setModelManager (const std::shared_ptr<const ModelManager>& model_manager_ptr)
{
    model_manager = model_manager_ptr;
}

void GameItem::loadModel()
{
    if (model_manager)
        setModel(model_manager->getModel(ID_));
}

std::shared_ptr<const ModelManager> GameItem::getModelManager() const
{
    return model_manager;
}

GameItem& GameItem::operator = (const GameItem& other){
    model_manager = other.model_manager;
    setID(other.ID_);
    return *this;
}
