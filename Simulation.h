#pragma once

#include "Matrix.h"

class Simulation {
private:
    Matrix s;
    int i;
public:
    Simulation(int, int);
    Matrix& get_matrix();

    void collision();
    void streaming();
    
};
