#include"matrix.h"

Matrix::Matrix() {
	rows = 0;
	columns = 0;
}

Matrix::Matrix(int rows, int columns) {
	this->rows = rows;
	this->columns = columns;
	v.resize(rows, vector<Cell>(columns, Cell()));
}

Cell Matrix::get_element(int i, int j) {
	return v[i][j];
}

void Matrix::set_element(int i, int j, Cell val) {
	v[i][j] = val;
}


void Matrix::prepare_environment() {
	random_device R;
	uniform_int_distribution<int> dist(0, 1);
	for (int i = 3; i < rows-3 && i < v.size(); i++) {
		for (int j = 3; j < columns/3-3 && j < v[i].size(); j++) {
			v[i][j] = Cell(dist(R) * 255,0,'0');
		}
		for (int j = columns / 3; j < columns-3 && j < v[i].size(); j++) {
			v[i][j].set_color(255);
		}
	}
	
	
}

void Matrix::opening_gate() {
	for (int i = rows / 2 - 5; i < rows / 2 + 5; i++) {
		for (int j = columns / 3 - 3; j < columns / 3; j++) {
			if (v[i][j].get_color() != 255)
				v[i][j].set_color(255);
			else
				v[i][j].set_color(122);
		}
	}
}

