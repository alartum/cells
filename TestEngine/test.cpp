#include "GraphField.h"
#include <ctime>
#include <thread>
#include <mutex>

void Thread(sf::Window & W, Field & F)
{
	W.setActive(true);
	while(W.isOpen())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		F.step();
        W.display();
	}
}

int main(int argc, char** argv, char** env)
{
	// Field size (in cells)
	const int Fsize = 300;
	// Cell size (in pixels)
	const int Csize = 2;

	srand(time(0));

	sf::RenderWindow W(sf::VideoMode(Fsize * Csize, Fsize * Csize), "Cells");
	W.setPosition(sf::Vector2i(200, 0));
	W.clear(sf::Color::White);

	Field F(W, Fsize, Csize);
	F.generate_field();

	W.setActive(false);
	std::thread T(Thread, std::ref(W), std::ref(F));


	while(W.isOpen()) {

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



