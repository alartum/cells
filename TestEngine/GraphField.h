#ifndef GRAPHFIELD_H_INCLUDED
#define GRAPHFIELD_H_INCLUDED

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <functional>
#include <thread>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/VideoMode.hpp>

class Cell
{
public:

	enum cell_type_t {Clear, Live};
	cell_type_t Type;
	cell_type_t PrevType;

	Cell();
	Cell(cell_type_t Tp);

	void setType(cell_type_t Tp);
	cell_type_t getType();
};


class Field
{
private:
	sf::RenderWindow & W;
	std::vector< std::vector< Cell > > Cells;
	size_t cell_size = 0;
	size_t field_size = 0;
	void set_cell_color(size_t x, size_t y, sf::Color cl);

public:
	Field(sf::RenderWindow & W, size_t field_size, size_t cell_size);

	void generate_field();
	void step();
};

#endif // GRAPHFIELD_H_INCLUDED
