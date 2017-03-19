#include "GraphField.h"
#include <ctime>
#include <thread>
#include <mutex>
#include <X11/Xlib.h>

void Thread(sf::Window & W, Field & F)
{
	W.setActive(true);
	while(W.isOpen())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		F.step();
		F.draw();
        W.display();
	}
}

int main(int argc, char** argv, char** env)
{
	// Field size (in cells)
	const int Fsize = 50;
	// Cell size (in pixels)
	const int Csize = 10;

	srand(time(0));

    XInitThreads();
	sf::RenderWindow W(sf::VideoMode(Fsize * Csize, Fsize * Csize), "Cells");
	W.setPosition(sf::Vector2i(200, 0));
	W.clear(sf::Color::White);

	Field F(W, Fsize, Csize);
	//F.load_from_file("field.txt");
	F.generate_field();
	F.draw_force();
	W.display();

	W.setActive(false);
	std::thread T(Thread, std::ref(W), std::ref(F));

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



