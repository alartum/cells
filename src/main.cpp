#include <thread>
#include <iostream>
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <X11/Xlib.h>
#include "item/item.hpp"
#include "model/model.hpp"
#include "matrix/matrix.hpp"

void UpdateThread(sf::RenderWindow& W, Matrix<Item>& items)
{
    W.setActive(true);
    int x_size = items.getWidth(), y_size = items.getHeight();

    while(W.isOpen()){
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        if (W.isOpen()) {
            W.clear();
            for (int i = 0; i < x_size; i++){
                for (int j = 0; j < y_size; j++){
                    Item& curr_item = items.at(i, j);
                    curr_item.nextFrame();
                    W.draw(curr_item);
                }
            }
            W.display();
        }
    }
}

int main(int argc, char** argv, char** env)
{
    XInitThreads();
    auto texture_ptr = std::make_shared<sf::Texture>();

    texture_ptr->loadFromFile("/home/alartum/programs/source/cells/src/tileinfo/tiles.png");
    auto waterModel_ptr = std::make_shared<Model>(1, texture_ptr);

    int tileSize = 32;
    waterModel_ptr->pushTextureRect(sf::IntRect(100, 694, tileSize, tileSize), 0);
    waterModel_ptr->pushTextureRect(sf::IntRect(430, 694, tileSize, tileSize), 0);

    Item waterItem(waterModel_ptr);

    size_t x_size = 10, y_size = 10;
    Matrix<Item> items(x_size, y_size, waterItem);
    for (int i = 0; i < x_size; i++){
        for (int j = 0; j < y_size; j++){
            items.at(i, j).setPosition(tileSize*i, tileSize*j);
        }
    }

    sf::RenderWindow W(sf::VideoMode(x_size*tileSize, y_size*tileSize), "Sprites");
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
}
