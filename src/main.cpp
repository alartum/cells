#include <thread>
#include <iostream>
#include <memory>

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <X11/Xlib.h>

#include "item/item.hpp"
#include "model/model.hpp"
#include "matrix/matrix.hpp"
#include "model_manager/modelmanager.hpp"
#include "generate_map/generatemap.hpp"

// for log messages
#include "debug.h"


void UpdateThread(sf::RenderWindow& W, Matrix<Tile>& items)
{
    W.setActive(true);
    int x_size = items.getWidth(), y_size = items.getHeight();

    while(W.isOpen()){
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        if (W.isOpen()) {
            W.clear();
            for (int i = 0; i < x_size; i++){
                for (int j = 0; j < y_size; j++){
                    Item& curr_item = items.at(i, j);
                    curr_item.nextFrame();
                    W.draw(curr_item);
                }
            }
            W.display();
        }
    }
}

int test_graph(int argc, char** argv, char** env)
{
    XInitThreads();
    auto texture_ptr = std::make_shared<sf::Texture>();

    texture_ptr->loadFromFile("tileinfo/tiles.png");
    auto waterModel_ptr = std::make_shared<Model>(1, texture_ptr);

    int tileSize = 32;
    waterModel_ptr->pushTextureRect(sf::IntRect(100, 694, tileSize, tileSize), 0);
    waterModel_ptr->pushTextureRect(sf::IntRect(430, 694, tileSize, tileSize), 0);

    ModelManager sample;
    sample.initSample();
    //Item waterItem(waterModel_ptr);
    Item waterItem;

    waterItem.setModel(sample.getModel(0));
    size_t x_size = 10, y_size = 10;
    Matrix<Item> items(x_size, y_size, waterItem);
    for (unsigned i = 0; i < x_size; i++){
        for (unsigned j = 0; j < y_size; j++){
            items.at(i, j).setPosition(tileSize*i, tileSize*j);
        }
    }

    sf::RenderWindow W(sf::VideoMode(x_size*tileSize, y_size*tileSize), "Sprites");
    W.setActive(false);
    W.setFramerateLimit(60);

    //std::thread T(UpdateThread, std::ref(W), std::ref(items));

    while(W.isOpen()){
        sf::Event event;
        while(W.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                W.close();
                break;
            }
        }
    }
    //T.join();

    return 0;
}//*/

int test_map_generetion(int argc, char** argv, char** env)
{
    size_t x_size = 10, y_size = 10;
    int tileSize = 32;
    std::shared_ptr< ModelManager > sample = std::make_shared< ModelManager >();
    sample->initSample();
    LOG("Model manager initialized");

    Matrix<Tile > items(x_size, y_size, Tile(1));
    LOG("Matrix initialized");
    
    for (unsigned i = 0; i < x_size; i++)
        for (unsigned j = 0; j < y_size; j++) {
            std::cout << i << " " << j << std::endl;
            items.at(i, j).setModelManager(sample);
            items.at(i, j).loadModel();
            items.at(i, j).setPosition(tileSize*i, tileSize*j);
        }
    LOG("Matrix of tile created");
        
        
    GenerateRandomMap mapGenerator(3, 0.01, 0.02, 20);
    std::cout << "I am here" << std::endl;
    mapGenerator(items);
    
    
    XInitThreads();
    
    sf::RenderWindow W(sf::VideoMode(x_size*tileSize, y_size*tileSize), "Sprites");
    W.setActive(false);
    W.setFramerateLimit(60);

    std::thread T(UpdateThread, std::ref(W), std::ref(items));

    while(W.isOpen()){
        sf::Event event;
        while(W.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                W.close();
                break;
            }
        }
    }
    T.join();
    
    return 0;
}


int main(int argc, char ** argv, char** env)
{
    test_map_generetion(argc, argv, env);
    return 0;
}
