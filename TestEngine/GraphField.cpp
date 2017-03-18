#include "GraphField.h"
////////////////////////////////////////////////////////
Cell::Cell() : Type(cell_type_t::Clear) {}
Cell::Cell(cell_type_t Tp) : Type(Tp) {}

void Cell::setType(cell_type_t Tp)
{
	Type = Tp;
}
Cell::cell_type_t Cell::getType()
{
	return Type;
}
/////////////////////////////////////////////////////////
Field::Field(sf::RenderWindow & W, size_t field_size, size_t cell_size) :
		W(W), field_size(field_size), cell_size(cell_size)
{
	Cells.resize(field_size);
	for (auto & row: Cells)
		row.resize(field_size);
}

void Field::set_cell_color(size_t x, size_t y, sf::Color cl)
{
    sf::ConvexShape polygon;
	polygon.setPointCount(4);
	polygon.setPoint(0, sf::Vector2f(0, 0));
	polygon.setPoint(1, sf::Vector2f(0, cell_size));
	polygon.setPoint(2, sf::Vector2f(cell_size, cell_size));
	polygon.setPoint(3, sf::Vector2f(cell_size, 0));
	polygon.setFillColor(cl);
	polygon.setPosition(x * cell_size, y * cell_size);
	W.draw(polygon);
}

// one game step, life Game for example
void Field::step()
{
	#pragma omp parallel for
    for(int i = 0; i < field_size; i++)
		for (int j = 0; j < field_size; j++)
			Cells[i][j].PrevType = Cells[i][j].Type;

	#pragma omp parallel for
    for(int i = 1; i < field_size - 1; i++)
		for (int j = 1; j < field_size - 1; j++)
			if (Cells[i][j].PrevType == Cell::cell_type_t::Clear) {
				int s = 0;
				for (int di = -1; di <= 1; di++)
					for (int dj = -1; dj <= 1; dj++)
						s += (Cells[i + di][j + dj].PrevType == Cell::cell_type_t::Live ? 1 : 0);
				if (s == 3) {
					Cells[i][j].Type = Cell::cell_type_t::Live;
				}
			}
			else {
				int s = 0;
				for (int di = -1; di <= 1; di++)
					for (int dj = -1; dj <= 1; dj++)
						s += (Cells[i + di][j + dj].PrevType == Cell::cell_type_t::Live ? 1 : 0);
				s -= 1;
				if (s < 2 || s > 3) {
					Cells[i][j].Type = Cell::cell_type_t::Clear;
				}
			}
}

void Field::draw()
{
	for(size_t i = 1; i < field_size - 1; i++)
		for (size_t j = 1; j < field_size - 1; j++)
			if (Cells[i][j].Type != Cells[i][j].PrevType) {
				if (Cells[i][j].Type == Cell::cell_type_t::Live)
					set_cell_color(i, j, sf::Color::Red);
				else
					set_cell_color(i, j, sf::Color::White);
			}
}

void Field::draw_force()
{
	for(size_t i = 1; i < field_size - 1; i++)
		for (size_t j = 1; j < field_size - 1; j++)
			if (Cells[i][j].Type == Cell::cell_type_t::Live)
				set_cell_color(i, j, sf::Color::Red);
			else
				set_cell_color(i, j, sf::Color::White);
}
// generator of test game field
void Field::generate_field()
{
    for(size_t i = 1; i < field_size- 1; i++)
		for (size_t j = 1; j < field_size - 1; j++) {
			Cells[i][j].PrevType = (rand() % 3 == 0 ? Cell::cell_type_t::Live : Cell::cell_type_t::Clear);
			Cells[i][j].Type = Cells[i][j].PrevType;
		}
}

void Field::load_from_file(std::string filename)
{
    std::fstream input;
    input.open(filename.c_str(), std::ios::in);
    for (int i = 0; i < field_size; i++)
		for (int j = 0; j < field_size; j++) {
			int tp;
			Cell::cell_type_t type;
			input >> tp;
			switch(tp) {
				case 0:
					type = Cell::Clear;
					break;
				case 1:
					type = Cell::Live;
					break;
				default:
					break;
			}
			Cells[i][j].Type = type;
			Cells[i][j].PrevType = type;
		}
	input.close();
}