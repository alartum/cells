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

void UpdateThread(Field& F)
{
       RandomMoving RM;
    F.setActive(true);

    while(F.isOpen()){
        //std::this_thread::sleep_for(std::chrono::milliseconds(800));
        if (F.isOpen()) {
            F.showAnimation();
            RM(F.mMap, F.mEntities);
            F.syncronize();
        }
    }
}


int test_field(int argc, char** argv, char** env) {
    XInitThreads();
    Field F;
    F.loadConfig("./tileinfo/config.lua");
    F.fitView();

    GenerateConnetedMap mapGenerator(5, 0.01, 0.2, 0.2);
    //GenerateRandomMap& gen = mapGenerator;
    F.generateTiles(mapGenerator);
    LOG("Map generated");

    GenerateRandomEntity entityGenerator(10, 1, 0, 30, 20, 1, 3, 9);
    F.generateEntities(entityGenerator);

    //MapDump()(F.mMap, F.mEntities);

    std::shared_ptr< ModelManager > sample = std::make_shared< ModelManager >();
    sample->loadConfig("tileinfo/mm_config.lua");
    LOG("Model manager initialized");
    F.setModelManager(sample);
    F.loadTileTextures();
    F.loadEntityTextures();
    LOG("Textures loaded");
    
    //for (auto & iter: F.mEntities) {
    //    std::cout << OBJECT_GRASS_EATING_ID << " " << OBJECT_PREDATOR_ID << " " << iter.getTypeID() << std::endl;
    //}
    
    //RandomMoving RM;
    /*
    std::cout << (void*)(&RM) << std::endl;
    
    for (int i = 0; i < 10000; i++) {
        MapDump()(F.mMap, F.mEntities);
        LOG("Map dumped");
        
        //F.generateEntities(entityGenerator);
        //F.doStep(RM);
        RM.operator()(F.mMap, F.mEntities);
        LOG("do step finished");
        sleep(1);
        F.syncronize();
        
    }*/

    //*/
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
