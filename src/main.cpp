#include <ctime>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <thread>
#include <chrono>

#include "field/field.hpp"

#include <X11/Xlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/VideoMode.hpp>

void Thread(Field & F, DoStep & S)
{
    F.setActive(true);
    while(F.isWindowOpen()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        F.doStep();
        if (F.isWindowOpen()) {
            F.draw();
            F.display();
        }
    }
}

int main(int argc, char** argv, char** env)
{
    XInitThreads();
        
    srand(time(NULL));

    TileInfo tileInfo;
    sf::Texture water;
    water.loadFromFile(sf::String("/home/alartum/programs/source/cells/src/tileinfo/tiles.png"),
                       sf::IntRect(330, 528, tileInfo.getTileSize().x,
                                   tileInfo.getTileSize().y));
    tileInfo.addTexture(Tile::Water, water);

    DoStep doStep;
    GenerateSampleTiles generateMap;
    GenerateObjects generateObjects;
    sf::Vector2u sizeTile(10, 10);

    Field F(sizeTile, generateObjects, generateMap, doStep, tileInfo);
    F.generate();
    F.draw();
    F.display();
    
    sf::RenderWindow& W = F.getWindow();
    W.setActive(false);
    std::thread T(Thread, std::ref(F), std::ref(doStep));
    
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
