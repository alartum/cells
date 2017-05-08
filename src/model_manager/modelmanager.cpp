#include <iostream>
#include "modelmanager.hpp"
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#define DEBUG
#include "../debug.h"
ModelManager::ModelManager()
{

}

std::shared_ptr<const Model> ModelManager::getModel(int typeID) const
{
    //LOG("[ModelManager.getModel()] typeID = %d", typeID);
    try{
        return mModels.at(typeID);
    }
    catch (...){
        try{
        //std::cerr << "[ModelManager] No model with ID = " << typeID << "\n";
        PERROR("No model with ID = 0x%x", typeID);
        LOG("Undefined: 0x%x", OBJECT_UNDEFINED_ID);
        return mModels.at(OBJECT_UNDEFINED_ID);
        }
        catch(...){
            //std::cerr << "[ModelManager] Invalid configuration\n";
            PERROR("Invalid configuration");
            return std::shared_ptr<const Model>();
        }
    }
}

void ModelManager::addModel(int typeID, const std::shared_ptr< const Model >& model_ptr)
{
    mModels.insert(std::pair<int, std::shared_ptr< const Model > >(typeID, model_ptr));
}
#define LOAD_VAR(var, from) \
{\
    auto obj = from[#var];\
    if (obj.valid()){\
        var = obj;\
    }\
    else{\
        PERROR("Can't find \"%s\" in %s", #var, #from);\
        return;\
    }\
}

void ModelManager::loadModel(const sol::table& properties){
    // Provide some basic info
    int id;
    LOAD_VAR(id, properties);
    std::string name;
    LOAD_VAR(name, properties);
    LOG("ITEM [%x] %s", id, name.c_str());

    // Load texture if not already loaded
    sol::table  model;
    LOAD_VAR(model, properties);
    std::string sprite_sheet;
    LOAD_VAR(sprite_sheet, model);
    auto& texture_ptr = mTextureMap[sprite_sheet];
    if (!texture_ptr){
        texture_ptr = std::make_shared<sf::Texture >();
        bool is_loaded = texture_ptr->loadFromFile(sprite_sheet);
        if (!is_loaded){
            texture_ptr.reset();
            PERROR("Can't load texture: %s", sprite_sheet.c_str());
            return;
        }
    }

    // Load the animation
    sol::table states;
    LOAD_VAR(states, model);
    auto model_ptr = std::make_shared<Model >(texture_ptr);
    model_ptr->setName(name);
    int animation_time = mAnimationTime;
    auto loadState = [&model_ptr, animation_time](sol::object key, sol::table state){
        sol::table frames;
        LOAD_VAR(frames, state);
        AnimationState state_cpy(frames.size()+1);
        std::string name;
        LOAD_VAR(name, state);
        state_cpy.setName(name);
        double global_frames;
        LOAD_VAR(global_frames, state);
        state_cpy.setAnimationTime(global_frames*animation_time);
        bool random_frame;
        LOAD_VAR(random_frame, state);
        state_cpy.setIsRandomFrame(random_frame);
        int stateNo = key.as<int>();
        LOG("[0x%x] %s", stateNo, name.c_str());
        auto loadFrame = [&state_cpy](sol::object key, sol::table frame){
            std::clog << "{" << key.as<int>() << "}";
            int frameNo = key.as<int>();
            sol::table top_left;
            LOAD_VAR(top_left, frame);
            int x, y;
            LOAD_VAR(x, top_left);
            LOAD_VAR(y, top_left);
            int top_left_x = x;
            int top_left_y = y;
            sol::table size;
            LOAD_VAR(size, frame);
            LOAD_VAR(x, size);
            LOAD_VAR(y, size);
            int size_x = x;
            int size_y = y;

            sf::IntRect rect(top_left_x, top_left_y, size_x, size_y);
            state_cpy.getRect(frameNo) = rect;
        };
        frames.for_each(loadFrame);
        model_ptr->loadAnimation(stateNo, state_cpy);
        std::clog << std::endl;
    };
    states.for_each(loadState);
    addModel(id, model_ptr);
}

#define print_type(info) std::system((std::string("c++filt -t ")  + typeid(info).name()).c_str())

void ModelManager::loadConfig(const std::string& mm_config_file){

    sol::state mm_config;
    mm_config.open_libraries(sol::lib::base, sol::lib::table, sol::lib::string);

    LOG("Loading config file: %s", mm_config_file.c_str());
    // Load file without execute
    sol::load_result config_script = mm_config.load_file(mm_config_file);
    if (!config_script.valid()){
        PERROR("Can't load config file: %s", mm_config_file.c_str());
        return;
    }
    // Execute under protection
    sol::protected_function_result config_result = config_script();
    if (!config_result.valid()){
        PERROR("Wrong config file format: %s", mm_config_file.c_str());
        return;
    }
    size_t animation_time;
    LOAD_VAR(animation_time, mm_config);
    mAnimationTime = animation_time;
    size_t max_FPS;
    LOAD_VAR(max_FPS, mm_config);
    mMaxFPS = max_FPS;
    size_t frame_delay;
    LOAD_VAR(frame_delay, mm_config);
    mFrameDelay = frame_delay;
    sol::table tile_size;
    LOAD_VAR(tile_size, mm_config);
    int x, y;
    LOAD_VAR(x, tile_size);
    LOAD_VAR(y, tile_size);
    mTileSize.x = x;
    mTileSize.y = y;
    std::string models_file;
    LOAD_VAR(models_file, mm_config);

    sol::state mm_models;
    mm_models.open_libraries(sol::lib::base, sol::lib::table, sol::lib::string);
    // VERY IMPORTANT PLACE: std::ref(*this) != *this
    // Only passing by reference allow access to class members
    mm_models.set_function("GameItem", &ModelManager::loadModel, std::ref(*this));
    LOG("Loading config file: %s", models_file.c_str());
    // Load file without execute
    sol::load_result models_script = mm_models.load_file(models_file);
    if (!models_script.valid()){
        PERROR("Can't load models file: %s", models_file.c_str());
        return;
    }
    // Execute under protection
    sol::protected_function_result models_result = models_script();
    if (!models_result.valid()){
        PERROR("Wrong models file format: %s", models_file.c_str());
        return;
    }
}
#undef LOAD_VAR

sf::Vector2u ModelManager::getTileSize() const{
    return mTileSize;
}

void ModelManager::setTileSize(sf::Vector2u size){
    mTileSize = size;

}

size_t ModelManager::getAnimationTime() const{
    return mAnimationTime;
}
void ModelManager::setAnimationTime(size_t animation_time){
    mAnimationTime = animation_time;
}


size_t ModelManager::getFrameDelay() const{
    return mFrameDelay;
}
void ModelManager::setFrameDelay(size_t frame_delay){
    mFrameDelay = frame_delay;
}


size_t ModelManager::getMaxFPS() const{
    return mMaxFPS;
}
void ModelManager::setMaxFPS(size_t max_FPS){
    mMaxFPS = max_FPS;
}
