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
        return models_.at(typeID);
    }
    catch (...){
        try{
        //PERROR("No model with ID = 0x%x", typeID);
        //LOG("Undefined: 0x%x", OBJECT_UNDEFINED_ID);
        return models_.at(OBJECT_UNDEFINED_ID);
        }
        catch(...){
            //PERROR("Invalid configuration");
            return std::shared_ptr<const Model>();
        }
    }
}

void ModelManager::addModel(int typeID, const std::shared_ptr< const Model >& model_ptr)
{
    models_.insert(std::pair<int, std::shared_ptr< const Model > >(typeID, model_ptr));
}

#define LOAD_VAR(var, from) \
{\
    auto obj = from[#var];\
    if (obj.valid()){\
        var = obj;\
    }\
    else{\
        std::string err_msg = "Can't find \"" #var "\" in " #from;\
        throw std::runtime_error(err_msg);\
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
    auto& texture_ptr = texture_map_[sprite_sheet];
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
    int animation_time = animation_time_;
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
            LOG("{%d}", key.as<int>());
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
    };
    states.for_each(loadState);
    addModel(id, model_ptr);
}

#define print_type(info) std::system((std::string("c++filt -t ")  + typeid(info).name()).c_str())

void ModelManager::loadConfig(const std::string& mm_config_file){

    sol::state mm_config;
    LOG("Loading config file: %s", mm_config_file.c_str());
    // Load and execute script
    // May throw!
    mm_config.script_file(mm_config_file, sol::default_on_error);

    size_t animation_time;
    LOAD_VAR(animation_time, mm_config);
    animation_time_ = animation_time;
    size_t max_FPS;
    LOAD_VAR(max_FPS, mm_config);
    max_FPS_ = max_FPS;
    size_t frame_delay;
    LOAD_VAR(frame_delay, mm_config);
    frame_delay_ = frame_delay;
    sol::table tile_size;
    LOAD_VAR(tile_size, mm_config);
    int x, y;
    LOAD_VAR(x, tile_size);
    LOAD_VAR(y, tile_size);
    tile_size_.x = x;
    tile_size_.y = y;
    std::string models_file;
    LOAD_VAR(models_file, mm_config);

    sol::state mm_models;
    // VERY IMPORTANT PLACE: std::ref(*this) != *this
    // Only passing by reference allow access to class members
    mm_models.set_function("GameItem", &ModelManager::loadModel, std::ref(*this));
    LOG("Loading config file: %s", models_file.c_str());
    // Load and execute script
    // May throw!
    mm_models.script_file(models_file, sol::default_on_error);
}
#undef LOAD_VAR

sf::Vector2u ModelManager::getTileSize() const{
    return tile_size_;
}

void ModelManager::setTileSize(sf::Vector2u size){
    tile_size_ = size;

}

size_t ModelManager::getAnimationTime() const{
    return animation_time_;
}
void ModelManager::setAnimationTime(size_t animation_time){
    animation_time_ = animation_time;
}


size_t ModelManager::getFrameDelay() const{
    return frame_delay_;
}
void ModelManager::setFrameDelay(size_t frame_delay){
    frame_delay_ = frame_delay;
}


size_t ModelManager::getMaxFPS() const{
    return max_FPS_;
}
void ModelManager::setMaxFPS(size_t max_FPS){
    max_FPS_ = max_FPS;
}
