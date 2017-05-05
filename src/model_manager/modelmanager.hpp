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
private:
    // Models with ID
    std::map<int, std::shared_ptr<const Model> > mModels;
    // Handler for Lua config
    void loadModel(const sol::table &prop);
    std::map<std::string, std::shared_ptr<sf::Texture> > mTextureMap;
};

#endif // MODELMANAGER_HPP
