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
#include "gamewindow/gamewindow.hpp"
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

    GenerateComplexMap mapGenerator(10, 0.02, 0.23, 0.2);
    //GenerateRandomMap& gen = mapGenerator;
    F.setGenerateMap(mapGenerator);
    F.generateTiles();
    LOG("Map generated");

    GenerateRandomEntity entityGenerator(10, 1, 0, 30, 40, 1, 3, 9);
    F.setGenerateEntities(entityGenerator);
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
    F.setDoStep(RM);
    F.setModelManager(sample);
    F.loadTileTextures();
    F.loadEntityTextures();
    LOG("Textures loaded");
    
    F.show();
    F.start();

    return a.exec();
}

int test_window(int argc, char** argv, char** env){
    QApplication a(argc, argv);
    GameWindow w;

    w.show();

    return a.exec();
}

int main(int argc, char ** argv, char** env)
{
    //test_field(argc, argv, env);
    return test_window(argc, argv, env);
}
