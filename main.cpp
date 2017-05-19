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
#include "do_step/dostep.hpp"
#include "field/field.hpp"

// for log messages
#define DEBUG
#include "debug.h"

void UpdateThread(Field& F, RandomMoving& RM)
{
    F.setActive(true);

    while(F.isOpen()){
        //std::this_thread::sleep_for(std::chrono::milliseconds(800));
        if (F.isOpen()) {
            F.showAnimation();
            RM(F.mMap, F.mEntities);
            F.syncronize();
//<<<<<<< HEAD
            //MapDump()(F.mMap, F.mEntities);
        }
//=======
//    }
//>>>>>>> 421e1273bf12e7a29879a2d224824168ccf65233
    }
}


int test_field(int argc, char** argv, char** env) {
    XInitThreads();
    Field F;
    F.loadConfig("./config/window_config.lua");
    F.fitView();

    GenerateConnetedMap mapGenerator(5, 0.01, 0.2, 0.2);
    //GenerateRandomMap& gen = mapGenerator;
    F.generateTiles(mapGenerator);
    LOG("Map generated");

    GenerateRandomEntity entityGenerator(10, 1, 0, 30, 40, 1, 3, 9);
    F.generateEntities(entityGenerator);
    //MapDump()(F.mMap, F.mEntities);
    //MapDump()(F.mMap, F.mEntities);

    std::shared_ptr< ModelManager > sample = std::make_shared< ModelManager >();
    sample->loadConfig("./config/mm_config.lua");
    LOG("Model manager initialized");
    RandomMoving RM(sample);
    F.setModelManager(sample);
    F.loadTileTextures();
    F.loadEntityTextures();
    LOG("Textures loaded");
    
    std::thread T(UpdateThread, std::ref(F), std::ref(RM));

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
