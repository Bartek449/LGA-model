#include"Cell.h"

Cell::Cell() {
	color = 122;
	population = 0;
	direction = '0';
}

Cell::Cell(int color, int population, char direction)  {
	this->color = color;
	this->population = population;
	this ->direction = direction;
}

int Cell::get_color() { return color; }
void Cell::set_color(int c) { color = c; }

int Cell::get_population() { return population; }
void Cell::set_population(int p) { population = p; }

char Cell::get_direction() { return direction; }
void Cell::set_direction(char d) { direction = d; }