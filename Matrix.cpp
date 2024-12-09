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

Cell& Matrix::get_element(int i, int j) { return v[i][j]; }

int Matrix::get_rows_num() const { return rows; }
int Matrix::get_columns_num() const { return columns; }

void Matrix::prepare_environment() {
	random_device R;
	uniform_int_distribution<int> dist(0, 1);
	uniform_int_distribution<int> dir(0, 3);
	vector<vector<int>> directions = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} };
	for (int i = 1; i < rows - 1 && i < v.size(); i++) {
		for (int j = 0; j < columns - 1; j++) {
			Cell& currentCell = v[i][j];
			if (j >= 2 && j < columns / 3 - 1)
			{
				if (dist(R) == 0) currentCell.set_info(directions[dir(R)]);
				else currentCell.set_info(EMPTY);
			}
			if ((j >= columns / 3 + 1 && j < columns - 2) || (i >= rows / 2 - 5 && i < rows / 2 + 5 && j >= columns / 3 - 1 && j < columns / 3 + 1))  currentCell.set_info(EMPTY);
		}

	}
}
