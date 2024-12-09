#include "Simulation.h"

Simulation::Simulation(int rows, int columns)
{
    s = Matrix(rows, columns);
}

Matrix& Simulation::get_matrix() { return s; }

void Simulation::collision() {
    Matrix next_matrix = s;
    vector<int> info;
    
    int rows = s.get_rows_num();
    int columns = s.get_columns_num();

    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < columns - 1; j++) {
            Cell& current_cell = s.get_element(i, j);
            Cell& next_cell = next_matrix.get_element(i, j);
            const vector<int>& info = current_cell.get_info();

            if (info[0] == 1 && info[2] == 1) next_cell.set_info({0,1,0,1});
         
            if (info[1] == 1 && info[3] == 1) next_cell.set_info({ 1,0,1,0 });
       
        }
    }

    s = next_matrix;
}

void Simulation::streaming() {


    Matrix next_matrix = s;
    vector<int> info;
    int rows = s.get_rows_num();
    int columns = s.get_columns_num();

    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < columns - 1; j++) {
            Cell& current_cell = s.get_element(i, j);
            Cell& next_cell = next_matrix.get_element(i, j);
            info = current_cell.get_info();

            if (info[0] == 1) {
                if (s.get_element(i, j + 1).get_info()!= WALL)  next_matrix.get_element(i, j + 1).set_direct_info(0, 1);
                else next_cell.set_direct_info(2, 1);
                next_cell.set_direct_info(0, 0);
            }
            if (info[1] == 1) {
                if (s.get_element(i + 1, j).get_info() != WALL) next_matrix.get_element(i + 1, j).set_direct_info(1, 1);
                else next_cell.set_direct_info(3, 1);
                next_cell.set_direct_info(1, 0);
            }
            if (info[2] == 1) {
                if (s.get_element(i, j - 1).get_info() != WALL) next_matrix.get_element(i, j - 1).set_direct_info(2, 1);
                else next_cell.set_direct_info(0, 1);
                next_cell.set_direct_info(2, 0);
            }
            if (info[3] == 1) {
                if (s.get_element(i - 1, j).get_info() != WALL) next_matrix.get_element(i - 1, j).set_direct_info(3, 1);
                else next_cell.set_direct_info(1, 1);
                next_cell.set_direct_info(3, 0);
            }
        }
    }

    s = next_matrix;
}