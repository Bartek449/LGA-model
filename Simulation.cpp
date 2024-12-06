#include "Simulation.h"

Simulation::Simulation(int rows, int columns)
{
    s = Matrix(rows, columns);
    s.prepare_environment();
}

Matrix& Simulation::get_matrix() { return s; }

void Simulation::collision() {
    Matrix next_matrix = s;  
    vector<int> info;

    for (int i = 1; i < s.get_rows_num() - 1; i++) {
        for (int j = 1; j < s.get_columns_num() - 1; j++) {
            Cell& current_cell = s.get_element(i, j);
            info = current_cell.get_info();

            if (info[0] == 1 && info[2] == 1) {
                if (s.get_element(i+1,j).get_color() != 122 && s.get_element(i-1, j).get_color() != 122) {
                    next_matrix.get_element(i-1, j).set_direct_info(1,1);
                    next_matrix.get_element(i+1, j).set_direct_info(3,1);
                    next_matrix.get_element(i, j).set_direct_info(0, 0);
                    next_matrix.get_element(i, j).set_direct_info(2, 0);
                }
                else if(s.get_element(i-1, j).get_color() == 122) {
                    next_matrix.get_element(i+1, j).set_direct_info(3,1);
                }
                else {
                    next_matrix.get_element(i-1, j).set_direct_info(1, 1);
                }
            }


            if (info[1] == 1 && info[3] == 1) {
                if (s.get_element(i, j-1).get_color() != 122 && s.get_element(i, j+1).get_color() != 122) {
                    next_matrix.get_element(i, j-1).set_direct_info(0,1);
                    next_matrix.get_element(i, j+1).set_direct_info(2,1);
                    next_matrix.get_element(i, j).set_direct_info(1, 0);
                    next_matrix.get_element(i, j).set_direct_info(3, 0);
                }
                else if (s.get_element(i, j-1).get_color() == 122) {
                    next_matrix.get_element(i, j+1).set_direct_info(2, 1);
                }
                else {
                    next_matrix.get_element(i, j-1).set_direct_info(0, 1);
                }
            }
        }
    }
    for (int i = 3; i < next_matrix.get_rows_num() - 3; i++) {
        for (int j = 3; j < next_matrix.get_columns_num() - 3; j++) {
            Cell& current_cell = next_matrix.get_element(i, j);
            info = current_cell.get_info();
            if (info != vector<int>{0, 0, 0, 0})
                current_cell.set_color(0);
            else if (info == vector<int>{0, 0, 0, 0}&& s.get_element(i, j).get_color() != 122)
                current_cell.set_color(255);
        }    
    }


    s = next_matrix;
}

void Simulation::streaming() {

    Matrix next_matrix = s;
    vector<int> info;

    for (int i = 1; i < s.get_rows_num() - 1; i++) {
        for (int j = 1; j < s.get_columns_num() - 1; j++) {
            Cell& current_cell = s.get_element(i, j);
            info = current_cell.get_info();

            if (info[0] == 1) {
                if (s.get_element(i, j - 1).get_color() != 122) {
                    next_matrix.get_element(i, j - 1).set_direct_info(0, 1);
                }
                else {
                    next_matrix.get_element(i, j+1).set_direct_info(2, 1);
                }
                next_matrix.get_element(i, j).set_direct_info(0, 0);
                //next_matrix.get_element(i, j).set_info({ 0,0,0,0 });
            }
            if (info[1] == 1) {
                if (s.get_element(i - 1, j).get_color() != 122) {
                    next_matrix.get_element(i - 1, j).set_direct_info(1, 1);
                }
                else {
                    next_matrix.get_element(i+1, j).set_direct_info(3, 1);
                }
                next_matrix.get_element(i, j).set_direct_info(1, 0);
                //next_matrix.get_element(i, j).set_info({ 0,0,0,0 });
            }
            if (info[2] == 1) {

                if (s.get_element(i, j + 1).get_color() != 122) {
                    next_matrix.get_element(i, j + 1).set_direct_info(2, 1);
                }
                else {
                    next_matrix.get_element(i, j-1).set_direct_info(0, 1);
                }
                next_matrix.get_element(i, j).set_direct_info(2, 0);
                //next_matrix.get_element(i, j).set_info({ 0,0,0,0 });
            }
            if (info[3] == 1) {

                if (s.get_element(i + 1, j).get_color() != 122) {
                    next_matrix.get_element(i + 1, j).set_direct_info(3, 1);;
                }
                else {
                    next_matrix.get_element(i - 1, j).set_direct_info(1, 1);
                }
                next_matrix.get_element(i, j).set_direct_info(3,0);
                //next_matrix.get_element(i, j).set_info({ 0,0,0,0 });
            }
            
        }
    }
    
    for (int i = 3; i < next_matrix.get_rows_num() - 3; i++) {
        for (int j = 3; j < next_matrix.get_columns_num() - 3; j++) {
            Cell& current_cell = next_matrix.get_element(i, j);
            info = current_cell.get_info();
            if (info != vector<int>{0, 0, 0, 0})
                current_cell.set_color(0);
            else if (info == vector<int>{0, 0, 0, 0} && s.get_element(i,j).get_color() != 122) 
                current_cell.set_color(255);
        }
    }
    s = next_matrix;
}