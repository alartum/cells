#include <ctime>
#include <thread>
#include <mutex>
#include <cstdlib>

#include "field/field.hpp"
#include "generator/generator.hpp"

int main(int argc, char** argv, char** env)
{
        //Field size (in pixels)
        const sf::Vector2u Fsize(500, 500);

        srand(time(NULL));

        sf::RenderWindow W(sf::VideoMode(Fsize.x, Fsize.y), "Cells");
        W.setPosition(sf::Vector2i(200, 0));
        W.clear(sf::Color::White);
        
    
        Field F(W, Fsize, sf::Color::White);
        LandscapeGenerator L(20, 10);

        F.generate(L);
        std::cout << F << std::endl;
        F.draw();

        W.display();


        while(W.isOpen()){
            sf::Event event;
            while(W.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    W.close();
                    break;
                }
            }
        }

       
        return 0;
}