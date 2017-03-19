#include <ctime>
#include <thread>
#include <mutex>
#include <cstdlib>

#include "field/field.hpp"
#include <X11/Xlib.h>

void Thread(sf::Window & W, Field & F, StepAlgorithm & L)
{
        W.setActive(true);
        while(W.isOpen())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            F.step(L);
            F.draw();
            W.display();
        }
}

int main(int argc, char** argv, char** env)
{
        //Field size (in cells)
        const sf::Vector2u Fsize(200, 200);
        // Cell size (in pixels)
        const int Csize = 3;

        srand(time(NULL));

        XInitThreads();
        sf::RenderWindow W(sf::VideoMode(Fsize.x * Csize, Fsize.y * Csize), "Cells");
        W.setPosition(sf::Vector2i(200, 0));
        W.clear(sf::Color::White);
        
        UniformRandomFieldGenerator G(Fsize, 0.3);
        LifeAlgorithm L;
        
        Field F(W, Fsize, Csize);

        F.generate(G);
        F.draw_forced();
        W.display();

        W.setActive(false);
        std::thread T(Thread, std::ref(W), std::ref(F), std::ref(L));

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