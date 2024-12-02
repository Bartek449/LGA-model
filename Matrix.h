#pragma once
#include <vector>
#include <random>

#include "Cell.h"

using namespace std;

class Matrix {
private:
    int rows, columns;
    vector <vector <Cell> > v;

public:
    Matrix();
    Matrix(int, int);

    Cell get_element(int, int);
    void set_element(int, int, Cell);
    int get_rows_num();
    int get_columns_num();
    vector <Cell> get_neighbours(int, int);
    void prepare_environment();
    void opening_gate();
};
