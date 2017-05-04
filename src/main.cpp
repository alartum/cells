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

void UpdateThread(Field& F)
{
    F.setActive(true);

    while(F.isOpen()){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (F.isOpen()) {
            F.clear();
            F.drawTiles();
            F.drawEntities();
            F.display();
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
     
    sf::Vector2u fieldSize(40, 40);
    sf::Vector2u tileSize(32, 32);
    sf::Vector2u windowSize(600, 600);

    Field F(fieldSize, windowSize, tileSize);
    GenerateRandomMap mapGenerator(5, 0.01, 0.1, 15);
    GenerateRandomMap& gen = mapGenerator;
    F.generateTiles(gen);
    LOG("Map generated");

    GenerateRandomEntity entityGenerator(3, 1, 0, 30, 1, 1, 0, 30);
    F.generateEntities(entityGenerator);

    std::shared_ptr< ModelManager > sample = std::make_shared< ModelManager >();
    sample->initSample();
    LOG("Model manager initialized");
    F.setModelManager(sample);
    F.loadTileTextures();
    F.loadEntityTextures();
    LOG("Textures loaded");
    F.fitView();
    
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
    
    std::thread T(UpdateThread, std::ref(F));

    while(F.isOpen()){
        sf::Event event;
        while(F.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                F.close();
                break;
            }
        }
    }
    T.join();
    
    return 0;
}

int test_algo(int argc, char** argv, char** env);

int main(int argc, char ** argv, char** env)
{
    srand(time(0));
    test_field(argc, argv, env);
    //test_algo(argc, argv, env);
    return 0;
}
