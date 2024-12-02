#include "Simulation.h"

Simulation::Simulation(int rows, int columns)
{
    s = Matrix(rows, columns); 
    s.prepare_environment();  
    iteration = 0;             
}



Matrix& Simulation::get_matrix() { return s; }

void Simulation::collision() {}

void Simulation::streaming() {}