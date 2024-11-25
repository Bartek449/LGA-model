#pragma once
#include <vector>
#include <random>

using namespace std;

class Matrix {
private:
    int rows, columns;
    vector <vector <int> > v;

public:
    Matrix();
    Matrix(int, int);

    int get_element(int, int);
    void set_element(int, int, int);
    Matrix randomize(int, int);
    void prepare_environment();
    
};
