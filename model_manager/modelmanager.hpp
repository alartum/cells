#ifndef MODELMANAGER_HPP
#define MODELMANAGER_HPP

#include <map>
#include "../model/model.hpp"
#include "../config/tile_ids.hpp"

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
    void loadConfig(const std::string& mm_config_file);
    size_t getAnimationTime() const;
    void setAnimationTime(size_t animation_time);

    size_t getFrameDelay() const;
    void setFrameDelay(size_t frame_delay);

    size_t getMaxFPS() const;
    void setMaxFPS(size_t max_FPS);

    void setTileSize(sf::Vector2u size);
    sf::Vector2u getTileSize() const;
private:
    // Models with ID
    std::map<int, std::shared_ptr<const Model> > mModels;
    // Handler for Lua config
    void loadModel(const sol::table &properties);
    std::map<std::string, std::shared_ptr<sf::Texture> > mTextureMap;
    // Appropriate tile size for the current texture pack
    sf::Vector2u mTileSize;
    // Number of ticks between the field updates
    // The animation frames are inserted uniformly
    size_t mAnimationTime;
    // Time is milliseconds between animation frames
    size_t mFrameDelay;
    size_t mMaxFPS;
};

#endif // MODELMANAGER_HPP
