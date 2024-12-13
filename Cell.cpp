#include"Cell.h"

Cell::Cell() : info(WALL) {}

Cell::Cell(vector<int> i) {
	if (info.size() != 4) throw invalid_argument("The info vector must have exactly 4 elements.");
	info = i;
}

void Cell::set_info(vector<int> i) {
	if (info.size() != 4)  throw invalid_argument("The info vector must have exactly 4 elements.");
    info = i; 
}
void Cell::set_direct_info(int i, int num) { 
	if (i < 0 || i >= info.size()) throw out_of_range("Index out of range in set_direct_info.");
	info[i] = num; 
}
const vector<int>& Cell::get_info() const { return info; }
