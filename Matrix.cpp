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

Cell& Matrix::get_element(int i, int j) {return v[i][j];}

int Matrix::get_rows_num() { return rows; }
int Matrix::get_columns_num() { return columns; }

vector<Cell> Matrix::get_neighbours(int i, int j) {
    vector<Cell> neighbours;

	if (j - 1 >= 0) neighbours.push_back(v[i][j - 1]); else neighbours.push_back(Cell());
	if (i - 1 >= 0)  neighbours.push_back(v[i-1][j]); else neighbours.push_back(Cell());
	if (j + 1 < columns)  neighbours.push_back(v[i][j+1]); else neighbours.push_back(Cell());
	if (i + 1 < rows)  neighbours.push_back(v[i+1][j]); else neighbours.push_back(Cell());

    return neighbours;
}


void Matrix::prepare_environment() {
	random_device R;
	int d;
	uniform_int_distribution<int> dist(0, 1);
	uniform_int_distribution<int> dir(1, 4);
	for (int i = 3; i < rows-3 && i < v.size(); i++) {
		for (int j = 3; j < columns/3-3 && j < v[i].size(); j++) {
			v[i][j] = Cell(dist(R) * 255, {0,0,0,0});
			if (v[i][j].get_color() == 0) {
				d = dir(R);
				if (d == 1)
					v[i][j].set_info({1,0,0,0});
				else if (d == 2)
					v[i][j].set_info({ 0,1,0,0 });
				else if (d == 3)
					v[i][j].set_info({ 0,0,1,0 });
				else 
					v[i][j].set_info({ 0,0,0,1 });
			}
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

