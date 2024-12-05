#include"Cell.h"

Cell::Cell() {
	color = 122;
	info = { 0,0,0,0 };
}

Cell::Cell(int color, vector<int> info)  {
	this->color = color;
	if (info.size() != 4) {
		info.resize(4, 0);
	}
	this->info = info;
}

void Cell::set_color(int c) { color = c; }
void Cell::set_info(vector<int> i) { info = i; }

vector<int> Cell::get_info() const { return info; }
int Cell::get_color() const { return color; }


bool Cell::is_empty() const {
	return color == 255;
}
bool Cell::is_wall() const {
	return color == 122;
}
bool Cell::is_gas() const {
	return color == 0;
}