#include <ctime>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <thread>
#include <chrono>

#include "field/field.hpp"
#include "generator/generator.hpp"

#include <X11/Xlib.h>

void Thread(Field & F, StepAlgorithm & S)
{
    F.setActive(true);
    while(F.isWindowOpen()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        F.action(S);
        if (F.isWindowOpen()) {
            F.draw();
            F.display();
        }
    }
}

int main(int argc, char** argv, char** env)
{
    XInitThreads();
    //Field size (in pixels)
    const sf::Vector2i Fsize(800, 800);
        
    srand(time(NULL));

    sf::RenderWindow W(sf::VideoMode(Fsize.x + 100, Fsize.y + 100), "Cells");
    W.setPosition(sf::Vector2i(200, 0));
    W.clear(sf::Color::White);
    
    Field F(W, sf::Vector2u(Fsize.x, Fsize.y), sf::Color::White);
    LandscapeGenerator L(500, 5);
    RandomMoving S(Fsize);
    
    F.generate(L);
    F.draw();
    F.display();
    
    W.setActive(false);
    std::thread T(Thread, std::ref(F), std::ref(S));   
    
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
    //*/
    return 0;
}