#include"Cell.h"

Cell::Cell() {
	info = WALL;
}

Cell::Cell(int color, vector<int> info) {
	if (info.size() != 4) {
		info.resize(4, 0);
	}
	this->info = info;
}

void Cell::set_info(vector<int> i) { info = i; }
void Cell::set_direct_info(int i, int num) { info[i] = num; }
vector<int> Cell::get_info() { return info; }
