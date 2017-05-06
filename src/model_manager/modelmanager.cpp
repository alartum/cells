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
        std::cerr << "[ModelManager] No model with ID = " << typeID << "\n";
        //LOG("Undefined: %d", OBJECT_UNDEFINED_ID);
        return mModels.at(OBJECT_UNDEFINED_ID);
        }
        catch(...){
            std::cerr << "[ModelManager] Invalid configuration\n";
            return std::shared_ptr<const Model>();
        }
    }
}

void ModelManager::addModel(int typeID, const std::shared_ptr< const Model >& model_ptr)
{
    mModels.insert(std::pair<int, std::shared_ptr< const Model > >(typeID, model_ptr));
}

void ModelManager::initSample()
{
    int tileSize = 32;
    auto texture_ptr = std::make_shared<sf::Texture>();

    bool is_loaded = texture_ptr->loadFromFile("./tileinfo/tiles.png");
    if (!is_loaded){
        return;
    }

    auto waterModel_ptr = std::make_shared< Model >(1, texture_ptr);
    waterModel_ptr->pushTextureRect(sf::IntRect(100, 694, tileSize, tileSize), 0);
    waterModel_ptr->pushTextureRect(sf::IntRect(430, 694, tileSize, tileSize), 0);
    addModel(TILE_WATER_ID, waterModel_ptr);

    auto grassModel_ptr = std::make_shared< Model >(1, texture_ptr);
    grassModel_ptr->pushTextureRect(sf::IntRect(34, 67, tileSize, tileSize), 0);
    // grassModel_ptr->pushTextureRect(sf::IntRect());
    addModel(TILE_GRASS_ID, grassModel_ptr);

    auto chicken_texture = std::make_shared<sf::Texture>();
    is_loaded = chicken_texture->loadFromFile("./tileinfo/chicken_eat.png");
    if (!is_loaded){
        return;
    }

    auto chickenModel_ptr = std::make_shared< Model >(4, chicken_texture);
    for (int k = 0; k < 4; k++){
        for (int i = 0; i < 4; i++){
            chickenModel_ptr->pushTextureRect(sf::IntRect(i * tileSize, k * tileSize, tileSize, tileSize), k);
        }
    }
    addModel(OBJECT_GRASS_EATING_ID, chickenModel_ptr);

    auto noModel_ptr = std::make_shared< Model >(1, texture_ptr);
    noModel_ptr->pushTextureRect(sf::IntRect(364, 1, tileSize, tileSize), 0);
    addModel(OBJECT_UNDEFINED_ID, noModel_ptr);
}

#define OUT_HEX std::hex << std::showbase
#define OUT_DEC std::dec << std::noshowbase

#define LOAD_VAR(var, from) \
{\
    auto obj = from[#var];\
    if (obj.valid()){\
        var = obj;\
    }\
    else{\
        std::cerr << "[Model Manager] Can't find \"" << #var << "\" in "\
                  << #from << "\n";\
        return;\
    }\
}

void ModelManager::loadModel(const sol::table& properties){
    // Provide some basic info
    int id;
    LOAD_VAR(id, properties);
    std::string name;
    LOAD_VAR(name, properties);
    std::clog << "[Model Manager] ITEM [" << OUT_HEX
              << id << OUT_DEC
              << "] " << name << std::endl;

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
            std::cerr << "[Model Manager] Can't load texture: " << sprite_sheet << std::endl;
            return;
        }
    }

    // Load the animation
    sol::table states;
    LOAD_VAR(states, model);
    auto model_ptr = std::make_shared<Model >(states.size() + 1, texture_ptr);
    bool random_frame;
    LOAD_VAR(random_frame, model);
    model_ptr->setIsRandomFrame(random_frame);
    auto loadState = [&model_ptr](sol::object key, sol::table state){
        std::string name;
        LOAD_VAR(name, state);
        int stateNo = key.as<int>();
        std::clog << "[Model Manager]\t\t[" << OUT_HEX
                  << stateNo << OUT_DEC << "] " << name;
        sol::table frames;
        LOAD_VAR(frames, state);
        std::vector<sf::IntRect>& animation = model_ptr->getAnimation(stateNo);
        animation.resize(frames.size() + 1);
        auto loadFrame = [&animation](sol::object key, sol::table frame){
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
            //std::cout << "[( " << top_left_x << "; "<< top_left_y << "), ( "
            //          <<  size_x << "; "<< size_y << ")]\n";
            animation[frameNo] = rect;
        };
        frames.for_each(loadFrame);
        std::clog << std::endl;
    };
    states.for_each(loadState);
    //int size = model_ptr->getTextureRectSeries(0).size();
    //LOG("Model: %d", size)
    addModel(id, model_ptr);
}

#undef LOAD_PARAM

#define print_type(info) std::system((std::string("c++filt -t ")  + typeid(info).name()).c_str())

void ModelManager::loadConfig(const std::string& filename){
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::table, sol::lib::string);

    // VERY IMPORTANT PLACE: std::ref(*this) != *this
    // Only passing by reference allow access to class members
    lua.set_function("GameItem", &ModelManager::loadModel, std::ref(*this));
    std::cerr << "[Model Manager] Loading config file: " << filename << std::endl;
    // Load file without execute
    sol::load_result script = lua.load_file(filename);
    if (!script.valid()){
        std::cerr << "[Model Manager] Can't load config file: " << filename << std::endl;
        return;
    }

    // Execute under protection
    sol::protected_function_result result = script();
    if (!result.valid()){
        std::cerr << "[Model Manager] Wrong config file format: " << filename << std::endl;
        return;
    }

    auto animation_ticks = lua["animation_ticks"];
    if (animation_ticks.valid()){
        mNAnimationTicks = animation_ticks;
    }
    else{
        std::cerr << "[Model Manager] Can't find \"animation_ticks\" in " << filename << "\n";
    }
    auto tile_size = lua["tile_size"];
    if (tile_size.valid()){
        auto tile_size_x = tile_size["x"];
        auto tile_size_y = tile_size["y"];
        if (tile_size_x.valid()){
            mTileSize.x = tile_size_x;
        }
        else{
            std::cerr << "[Model Manager] Can't find \"tile_size.x\" in " << filename << "\n";
        }
        if (tile_size_y.valid()){
            mTileSize.y = tile_size_y;
        }
        else{
            std::cerr << "[Model Manager] Can't find \"tile_size.y\" in " << filename << "\n";
        }
    }
    else{
        std::cerr << "[Model Manager] Can't find \"tile_size\" in " << filename << "\n";
    }
    /*sf::IntRect rect = mModels[257]->getTextureRectSeries(0).at(1);
    LOG("Final: %d", mModels[257]->getTextureRectSeries(0).size());
    LOG("Final left: %d", rect.left);*/;
}

sf::Vector2u ModelManager::getTileSize() const{
    return mTileSize;
}

void ModelManager::setTileSize(sf::Vector2u size){
    mTileSize = size;

}

void ModelManager::setNAnimationTicks(int nAnimationTicks){
    mNAnimationTicks = nAnimationTicks;
}

int ModelManager::getNAnimationTicks() const{
    return mNAnimationTicks;
}
