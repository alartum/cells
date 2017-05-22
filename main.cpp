#include <QApplication>

#include <thread>
#include <iostream>
#include <memory>

#include "field/field.hpp"
#include "item/item.hpp"
#include "model/model.hpp"
#include "matrix/matrix.hpp"
#include "model_manager/modelmanager.hpp"
#include "generate_map/generatemap.hpp"
#include "do_step/dostep.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

// for log messages
#define DEBUG
#include "debug.h"

int test_field(int argc, char** argv, char** env) {
    QApplication a(argc, argv);
    Field F;
    try{
        F.loadConfig("./config/window_config.lua");
    } catch (std::exception& err){
        PERROR("%s", err.what());
        return EXIT_FAILURE;
    }

    GenerateConnetedMap mapGenerator(5, 0.01, 0.2, 0.2);
    //GenerateRandomMap& gen = mapGenerator;
    F.generate_map_ = mapGenerator;
    F.generateTiles();
    LOG("Map generated");

    GenerateRandomEntity entityGenerator(10, 1, 0, 30, 40, 1, 3, 9);
    F.generate_entities_ = entityGenerator;
    F.generateEntities();
    //MapDump()(F.mMap, F.mEntities);
    //MapDump()(F.mMap, F.mEntities);

    std::shared_ptr< ModelManager > sample = std::make_shared< ModelManager >();
    try{
        sample->loadConfig("./config/mm_config.lua");
    } catch (std::exception& err){
        PERROR("%s", err.what());
        return EXIT_FAILURE;
    }
    LOG("Model manager initialized");
    RandomMoving RM(sample);
    F.do_step_ = RM;
    F.setModelManager(sample);
    F.loadTileTextures();
    F.loadEntityTextures();
    LOG("Textures loaded");
    
    F.show();
    F.start();

    return a.exec();
}

int test_algo(int argc, char** argv, char** env);

int main(int argc, char ** argv, char** env)
{
    srand(time(0));
    test_field(argc, argv, env);
    //test_algo(argc, argv, env);
    return 0;
}
