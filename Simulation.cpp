#include "Simulation.h"

Simulation::Simulation(int rows, int columns) : s(rows, columns) {}

Matrix& Simulation::get_matrix() { return s; }

void Simulation::collision() {
    Matrix next_matrix = s;
    int rows = s.get_rows_num();
    int columns = s.get_columns_num();
    vector<int> left_right{ 1, 0, 1, 0 };
    vector<int> up_down{ 0, 1, 0, 1 };

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            const vector<int>& info = s.get_element(i, j).get_info();
            Cell& future_cell = next_matrix.get_element(i, j);

            if (info == left_right) future_cell.set_info(up_down);
            if (info == up_down) future_cell.set_info(left_right);
            
        }
    }

    s = next_matrix;
}


void Simulation::streaming() {
    Matrix next_matrix = s;
    int rows = s.get_rows_num();
    int columns = s.get_columns_num();

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            if (s.get_element(i, j).get_info() != WALL) {
                for (int d = 0; d < 4; d++) {
                    next_matrix.get_element(i, j).set_direct_info(d, 0); 
                }
            }
        }
    }

    for (size_t i = 1; i < rows - 1; i++) {
        for (size_t j = 1; j < columns - 1; j++) {
            Cell& current_cell = s.get_element(i, j);
            vector<int> info = current_cell.get_info();

            if (info[0] == 1) {
                Cell& right_cell = s.get_element(i, j + 1);
                if (right_cell.get_info() == WALL) {
                    next_matrix.get_element(i, j).set_direct_info(2, 1);
                }
                else {
                    next_matrix.get_element(i, j + 1).set_direct_info(0, 1);
                }
            }
            if (info[1] == 1) { 
                Cell& down_cell = s.get_element(i + 1, j);
                if (down_cell.get_info() == WALL) {
                    next_matrix.get_element(i, j).set_direct_info(3, 1);
                }
                else {
                    next_matrix.get_element(i + 1, j).set_direct_info(1, 1);
                }
            }
            if (info[2] == 1) { 
                Cell& left_cell = s.get_element(i, j - 1);
                if (left_cell.get_info() == WALL) {
                    next_matrix.get_element(i, j).set_direct_info(0, 1);
                }
                else {
                    next_matrix.get_element(i, j - 1).set_direct_info(2, 1);
                }
            }
            if (info[3] == 1) { 
                Cell& up_cell = s.get_element(i - 1, j);
                if (up_cell.get_info() == WALL) {
                    next_matrix.get_element(i, j).set_direct_info(1, 1);
                }
                else {
                    next_matrix.get_element(i - 1, j).set_direct_info(3, 1);
                }
            }
        }
    }

    s = next_matrix;
}
