#ifndef GAMEITEM_HPP
#define GAMEITEM_HPP

#include "../item/item.hpp"
#include "../model_manager/modelmanager.hpp"
#include <memory>

class GameItem : public Item
{
public:
    GameItem(int typeID = 0,
             const sf::Vector2u& latticePosition = sf::Vector2u(0,0),
             unsigned state = 0);
    int getTypeID() const;
    // Updates ID and reloads the texture
    //! Time expensive
    void setTypeID(int TypeID);
    void setModelManager (const std::shared_ptr<const ModelManager>& modelManager_ptr);
    std::shared_ptr<const ModelManager> getModelManager() const;
    void loadModel();
    GameItem& operator = (const GameItem& other);
    
protected:
    // Type ID to handle textures correctly
    int mTypeID;
    // Model that provides textures
    std::shared_ptr<const ModelManager> mModelManager;
};

#endif // GAMEITEM_HPP
