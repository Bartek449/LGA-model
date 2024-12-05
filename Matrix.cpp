#include"matrix.h"

Matrix::Matrix() {
	rows = 0;
	columns = 0;
}

Matrix::Matrix(int rows, int columns) {
	this->rows = rows;
	this->columns = columns;
	v.resize(rows); 
	for (int i = 0; i < rows; ++i) {
		v[i].resize(columns); 
	}
}
Matrix::Matrix(const Matrix& other) {
	this->rows = other.get_rows_num();
	this->columns = other.get_columns_num();

	v.resize(rows);
	for (int i = 0; i < rows; ++i) {
		v[i].resize(columns);
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			v[i][j] = other.v[i][j];
		}
	}
}
Matrix Matrix::clone() const {
	return Matrix(*this);  
}

Cell& Matrix::get_element(int i, int j) {return v[i][j];}

int Matrix::get_rows_num() const{ return rows; }
int Matrix::get_columns_num() const { return columns; }

vector<Cell*> Matrix::get_neighbours(int i, int j) {
	vector<Cell*> neighbours;
	if (j - 1 >= 0) neighbours.push_back(&v[i][j - 1]); else neighbours.push_back(NULL);
	if (i - 1 >= 0) neighbours.push_back(&v[i - 1][j]); else neighbours.push_back(NULL);
	if (j + 1 < columns) neighbours.push_back(&v[i][j + 1]); else neighbours.push_back(NULL);
	if (i + 1 < rows) neighbours.push_back(&v[i + 1][j]); else neighbours.push_back(NULL);
	return neighbours;
}


void Matrix::prepare_environment() {
	std::cout << "Preparing environment...\n";
	random_device R;
	uniform_int_distribution<int> dist(0, 1);
	uniform_int_distribution<int> dir(0, 3);

	for (int i = 3; i < rows - 3 && i < v.size(); i++) {
		for (int j = 3; j < columns / 3 - 3 && j < v[i].size(); j++) {
			Cell& currentCell = v[i][j];
			currentCell.set_color(dist(R) * 255); 

			if (currentCell.get_color() == 0) { 
				int d = dir(R);
				vector<vector<int>> directions = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} };
				currentCell.set_info(directions[d]);  
			}
		}

		for (int j = columns / 3; j < columns - 3 && j < v[i].size(); j++) {
			v[i][j].set_color(255);  
		}
	}
}


void Matrix::opening_gate() {
	for (int i = rows / 2 - 5; i < rows / 2 + 5; ++i) {
		for (int j = columns / 3 - 3; j < columns / 3; ++j) {
			Cell& currentCell = v[i][j];
			if (currentCell.get_color() != 255) {
				currentCell.set_color(255); 
			}
			else {
				currentCell.set_color(122);  
			}
		}
	}
}

