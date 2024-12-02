#include"Cell.h"

Cell::Cell() {
	color = 122;
	info = { 0,0,0,0 };
}

Cell::Cell(int color, vector<int> info)  {
	this->color = color;
	this->info = info;
}

void Cell::set_color(int c) { color = c; }
void Cell::set_info(vector<int> i) { info = i; }

vector<int> Cell::get_info() const { return info; }
int Cell::get_color() const { return color; }