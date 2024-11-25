#include"matrix.h"

Matrix::Matrix() {
	rows = 0;
	columns = 0;
}

Matrix::Matrix(int rows, int columns) {
	this->rows = rows;
	this->columns = columns;
	v.resize(rows, vector<int>(columns, 122));
}

int Matrix::get_element(int i, int j) {
	return v[i][j];
}

void Matrix::set_element(int i, int j, int val) {
	v[i][j] = val;
}

Matrix Matrix::randomize(int a, int b) {
	Matrix M(a, b);
	random_device R;
	uniform_int_distribution<int> dist(0, 1);
	for (int i = 0; i < M.v.size(); i++) {
		for (int j = 0; j < M.v[i].size(); j++) {
			M.v[i][j] = dist(R) * 255;
		}
	}
	return M;
}

void Matrix::prepare_environment() {
	random_device R;
	uniform_int_distribution<int> dist(0, 1);
	for (int i = 3; i < rows-3 && i < v.size(); i++) {
		for (int j = 3; j < columns/3-3 && j < v[i].size(); j++) {
			v[i][j] = dist(R) * 255;
		}
		for (int j = columns / 3; j < columns-3 && j < v[i].size(); j++) {
			v[i][j] = 255;
		}
	}
	
	for (int i = rows/2-5; i < rows/2+5; i++) {
		for (int j = columns / 3 - 3; j < columns / 3; j++) {
			v[i][j] = 255;
		}
	}
}

