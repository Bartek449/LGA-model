#include "Simulation.h"
enum Direction { RIGHT = 0, DOWN = 1, LEFT = 2, UP = 3 };

Simulation::Simulation(int rows, int columns) : s(rows, columns) {}

Matrix& Simulation::get_matrix() { return s; }

void Simulation::collision() {
    Matrix next_matrix = s;
    int rows = s.get_rows_num();
    int columns = s.get_columns_num();

    for (size_t i = 1; i < rows - 1; i++) {
        for (size_t j = 1; j < columns - 1; j++) { 
            Cell& future_cell = next_matrix.get_element(i, j);
            const vector<int>& info = s.get_element(i, j).get_info();

            if (info[RIGHT] == 1 && info[LEFT] == 1) future_cell.set_info({ 0,1,0,1 });
            if (info[DOWN] == 1 && info[UP] == 1) future_cell.set_info({ 1,0,1,0 });
        }
    }

    s = next_matrix;
}

void Simulation::streaming() {
    Matrix next_matrix = s;
    int rows = s.get_rows_num();
    int columns = s.get_columns_num();

    for (size_t i = 1; i < rows - 1; i++) {
        for (size_t j = 1; j < columns - 1; j++) {
            Cell& current_cell = s.get_element(i, j);
            const vector<int>& info = current_cell.get_info();
            Cell& future_cell = next_matrix.get_element(i, j);
            Cell& right_cell = s.get_element(i, j + 1);
            Cell& down_cell = s.get_element(i + 1, j);
            Cell& left_cell = s.get_element(i, j - 1);
            Cell& up_cell = s.get_element(i - 1, j);

            vector<int> new_info = future_cell.get_info();

            if (info[RIGHT] == 1) {
                future_cell.set_direct_info(0, 0);
                if (right_cell.get_info() == WALL) {
                    future_cell.set_direct_info(2, 1);
                } else if(right_cell.get_info()[2]!= 1) {
                    next_matrix.get_element(i, j + 1).set_direct_info(0, 1);
                }
                else {
                    future_cell.set_direct_info(1, 1);
                }
            }
            if (info[DOWN] == 1) {
               
                future_cell.set_direct_info(1, 0);
                if (down_cell.get_info() == WALL) {
                    future_cell.set_direct_info(3, 1);
                } else if (down_cell.get_info()[3] != 1) {
                    next_matrix.get_element(i + 1, j).set_direct_info(1, 1);
                }
                else {
                    future_cell.set_direct_info(2, 1);
                }
            }
            if (info[LEFT] == 1) {
                
                future_cell.set_direct_info(2, 0);
                if (left_cell.get_info() == WALL) {
                    future_cell.set_direct_info(0, 1);
                } else if (left_cell.get_info()[0] != 1) {
                    next_matrix.get_element(i, j - 1).set_direct_info(2, 1);
                }
                else
                {
                    future_cell.set_direct_info(3, 1);
                }
            }
            if (info[UP] == 1) {
               
                future_cell.set_direct_info(3, 0);
                if (up_cell.get_info() == WALL) {
                    future_cell.set_direct_info(1, 1);
                } else if (up_cell.get_info()[1] != 1) {
                    next_matrix.get_element(i - 1, j).set_direct_info(3, 1);
                }
                else {
                    future_cell.set_direct_info(0, 1);
                }
            }

            
           
        }
    }

        s = next_matrix;
}
