#include"Cell.h"

Cell::Cell() {
	color = 122;
	info = { 0,0,0,0 };
}

Cell::Cell(int color, vector<int> info) {
	this->color = color;
	if (info.size() != 4) {
		info.resize(4, 0);
	}
	this->info = info;
}

void Cell::set_color(int c) { color = c; }
void Cell::set_info(vector<int> i) { info = i; }

void Cell::set_direct_info(int i, int num) {
	info[i] = num;
}

vector<int> Cell::get_info() { return info; }
int Cell::get_color() const { return color; }