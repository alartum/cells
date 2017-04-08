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
    mModels.insert(std::pair<int, std::shared_ptr<Model> >(typeID, model_ptr));
}

void ModelManager::initSample()
{
    // Example
    auto texture_ptr = std::make_shared<sf::Texture>();

    texture_ptr->loadFromFile("/home/alartum/programs/source/cells/src/tileinfo/tiles.png");
    auto waterModel_ptr = std::make_shared<const Model>(1, texture_ptr);

    int tileSize = 32;
    waterModel_ptr->pushTextureRect(sf::IntRect(100, 694, tileSize, tileSize), 0);
    waterModel_ptr->pushTextureRect(sf::IntRect(430, 694, tileSize, tileSize), 0);

    loadModel(0, waterModel_ptr);
}
