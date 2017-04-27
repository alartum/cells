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
#include "field/field.hpp"

// for log messages
#include "debug.h"


void UpdateThread(sf::RenderWindow& W, Field& F)
{
    F.setActive(true);

    while(W.isOpen()){
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        if (W.isOpen()) {
            W.clear();
            F.drawTiles();
            W.display();
        }
    }
}

/*
int test_map_generation(int argc, char** argv, char** env)
{
    size_t x_size = 40, y_size = 40;
    int tileSize = 32;
    std::shared_ptr< ModelManager > sample = std::make_shared< ModelManager >();
    sample->initSample();
    LOG("Model manager initialized");

    Matrix<Tile > items(x_size, y_size, Tile(1));
    LOG("Matrix initialized");
    
    for (unsigned i = 0; i < x_size; i++)
        for (unsigned j = 0; j < y_size; j++) {
            items.at(i, j).setModelManager(sample);
            items.at(i, j).loadModel();
            items.at(i, j).setPosition(tileSize*i, tileSize*j);
        }
    LOG("Matrix of tile created");
        
        
    GenerateRandomMap mapGenerator(8, 0.01, 0.06, 15);
    mapGenerator(items);
    
    
    XInitThreads();
    
    sf::RenderWindow W(sf::VideoMode(x_size * tileSize, y_size * tileSize), "Sprites");
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
}*/


int test_field(int argc, char** argv, char** env) {
    XInitThreads();
     
    size_t x_size = 40, y_size = 40;
    sf::Vector2u fieldSize(x_size, y_size);
    
    int tileSize = 32;
    std::shared_ptr< ModelManager > sample = std::make_shared< ModelManager >();
    sample->initSample();
    LOG("Model manager initialized");

    sf::RenderWindow W(sf::VideoMode(x_size * tileSize, y_size * tileSize), "Sprites");
    W.setFramerateLimit(60);
    Field F(W, fieldSize, tileSize);
    F.setModelManager(sample);
    F.setActive(false);
    
    GenerateRandomMap mapGenerator(8, 0.01, 0.06, 15);
    GenerateRandomMap& gen = mapGenerator;
    F.generateTiles(gen);
    
    /*for (int i = 0; i < F.mMap.getHeight(); i++) {
        for (int j = 0; j < F.mMap.getWidth(); j++) {
            if (F.mMap.at(i, j).getTypeID() == TILE_GRASS_ID) 
                std::cout << "\x1b[42m\x1b[1m";
            else
                std::cout << "\x1b[34m";
            std::cout << "  ";
            std::cout << "\x1b[44m";
        }
        std::cout << std::endl;
    }*/
    
    std::thread T(UpdateThread, std::ref(W), std::ref(F));

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
    test_field(argc, argv, env);
    return 0;
}
