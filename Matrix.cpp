#include"matrix.h"

Matrix::Matrix() : rows(0), columns(0), v() {}

Matrix::Matrix(int rows, int columns) : rows(rows), columns(columns), v(rows, vector<Cell>(columns)) {
	if (rows <= 0 || columns <= 0) {
		throw invalid_argument("Matrix dimensions must be greater than zero.");
	}
}

Matrix::Matrix(const Matrix& other): rows(other.rows), columns(other.columns), v(other.v) {}
	
int Matrix::get_rows_num() const { return rows; }
int Matrix::get_columns_num() const { return columns; }

Cell& Matrix::get_element(int i, int j) {
	if (i < 0 || i >= rows || j < 0 || j >= columns) throw out_of_range("Index out of range in get_element.");
	return v[i][j];
}




void Matrix::prepare_environment() {
	mt19937 rng(random_device{}());
	uniform_int_distribution<int> dist(0, 100);
	uniform_int_distribution<int> dir(0, 3);
	vector<vector<int>> directions = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} };
	for (size_t i = 1; i < rows - 1 && i < v.size(); i++) {
		for (size_t j = 0; j < columns - 1; j++) {
			Cell& currentCell = v[i][j];
			if (j >= 2 && j < columns / 3 - 1)
			{
				currentCell.set_info(directions[dir(rng)]);
				//if (dist(rng) < 100) currentCell.set_info(directions[dir(rng)]);
				//else currentCell.set_info(EMPTY);
			}
			if ((j >= columns / 3 + 1 && j < columns - 2) || (i >= rows / 2 - 3 && i < rows / 2 + 3 && j >= columns / 3 - 1 && j < columns / 3 + 1))  currentCell.set_info(EMPTY);
		}

	}
}
