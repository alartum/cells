#include <iostream>
#include "modelmanager.hpp"
#include <memory>
#include <SFML/Graphics/Texture.hpp>

ModelManager::ModelManager()
{

}

std::shared_ptr<const Model> ModelManager::getModel(int typeID) const
{
    return mModels.at(typeID);
}

void ModelManager::loadModel(int typeID, const std::shared_ptr<const Model>& model_ptr)
{
    //mModels.insert(std::make_pair<int, std::shared_ptr<Model> >(typeID, model_ptr));
    mModels[typeID] = model_ptr;
}

void ModelManager::initSample()
{
    int tileSize = 32;
    auto texture_ptr = std::make_shared<sf::Texture>();
    texture_ptr->loadFromFile("tileinfo/tiles.png");
    
    auto waterModel_ptr = std::make_shared< Model >(1, texture_ptr);
    waterModel_ptr->pushTextureRect(sf::IntRect(100, 694, tileSize, tileSize), 0);
    waterModel_ptr->pushTextureRect(sf::IntRect(430, 694, tileSize, tileSize), 0);
    loadModel(TILE_WATER_ID, waterModel_ptr);
    
    auto grassModel_ptr = std::make_shared< Model >(1, texture_ptr);
    grassModel_ptr->pushTextureRect(sf::IntRect(32, 32, tileSize, tileSize), 0);
    // grassModel_ptr->pushTextureRect(sf::IntRect());
    loadModel(TILE_GRASS_ID, grassModel_ptr);    
}
