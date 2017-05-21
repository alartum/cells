#ifndef GAMEITEM_HPP
#define GAMEITEM_HPP

#include "../item/item.hpp"
#include "../model_manager/modelmanager.hpp"
#include <memory>

class GameItem : public Item
{
public:
    GameItem(int typeID = 0,
             const sf::Vector2f& position = sf::Vector2f(0,0),
             unsigned state = 0);
    int getID() const;
    // Updates ID and reloads the texture
    //! Time expensive
    void setID(int ID);
    void setModelManager (const std::shared_ptr<const ModelManager>& model_manager_ptr);
    std::shared_ptr<const ModelManager> getModelManager() const;
    void loadModel();
    GameItem& operator = (const GameItem& other);
    std::map< std::string, int > properties;

protected:
    // Type ID to handle textures correctly
    int ID_;
    // Model that provides textures
    std::shared_ptr<const ModelManager> model_manager;
};

#endif // GAMEITEM_HPP
