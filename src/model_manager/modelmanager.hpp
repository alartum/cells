#ifndef MODELMANAGER_HPP
#define MODELMANAGER_HPP

#include <map>
#include "../model/model.hpp"
#include "../tileinfo/tile_ids.hpp"

#include <string>
#include <iomanip>
#include <sol.hpp>

class ModelManager
{
public:
    ModelManager();
    std::shared_ptr<const Model> getModel(int typeID) const;
    void addModel(int typeID, const std::shared_ptr<const Model>& model_ptr);
    void initSample();
    void loadConfig(const std::string& filename);

    void setTileSize(sf::Vector2u size);
    sf::Vector2u getTileSize() const;

    void setNAnimationTicks(int nAnimationTicks);
    int getNAnimationTicks() const;
private:
    // Models with ID
    std::map<int, std::shared_ptr<const Model> > mModels;
    // Handler for Lua config
    void loadModel(const sol::table &properties);
    std::map<std::string, std::shared_ptr<sf::Texture> > mTextureMap;
    // Appropriate tile size for the current texture pack
    sf::Vector2u mTileSize;
    // Appropriate animation cycle length
    int mNAnimationTicks;
};

#endif // MODELMANAGER_HPP
