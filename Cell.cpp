#include"Cell.h"

Cell::Cell() {
	color = 122;
	vector<int> info = { 0,0,0,0 };
}

Cell::Cell(int color, vector<int> info)  {
	this->color = color;
	this->info = info;
}

int Cell::get_color() { return color; }
void Cell::set_color(int c) { color = c; }

vector<int> Cell::get_info() { return info; }
void Cell::set_info(vector<int> i) { info = i; }
