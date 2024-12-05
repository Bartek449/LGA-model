#include "Simulation.h"

Simulation::Simulation(int rows, int columns)
{
    s = Matrix(rows, columns);
    s.prepare_environment();
}

Matrix& Simulation::get_matrix() { return s; }

void Simulation::collision() {
    Matrix next_matrix = s;  // Tworzymy kopiê matrix, aby zachowaæ poprzedni stan
    vector<Cell*> neigh;
    vector<int> info;

    for (int i = 1; i < s.get_rows_num() - 1; i++) {
        for (int j = 1; j < s.get_columns_num() - 1; j++) {
            Cell& current_cell = s.get_element(i, j);
            neigh = s.get_neighbours(i, j);
            info = current_cell.get_info();

            if (info[0] == 1 && info[2] == 1) {  
                if (s.get_element(i, j - 1).get_color() != 122 && s.get_element(i, j + 1).get_color() != 122) {
                    next_matrix.get_element(i, j - 1).set_info({ 0, 1, 0, 0 });
                    next_matrix.get_element(i, j + 1).set_info({ 0, 0, 0, 1 });
                    next_matrix.get_element(i, j).set_color(255); 
                    next_matrix.get_element(i, j).set_info({ 0, 0, 0, 0 });
                }
                else {
                    next_matrix.get_element(i, j).set_info({ 0, 0, 1, 0 });
                    next_matrix.get_element(i, j).set_color(0);
                }
            }

            
            if (info[1] == 1 && info[3] == 1) {  
                if (s.get_element(i - 1, j).get_color() != 122 && s.get_element(i + 1, j).get_color() != 122) {
                    next_matrix.get_element(i - 1, j).set_info({ 1, 0, 0, 0 });
                    next_matrix.get_element(i + 1, j).set_info({ 0, 0, 1, 0 });
                    next_matrix.get_element(i, j).set_color(255);
                    next_matrix.get_element(i, j).set_info({ 0, 0, 0, 0 });
                }
                else {
                    next_matrix.get_element(i, j).set_info({ 0, 0, 0, 1 });
                    next_matrix.get_element(i, j).set_color(0);
                }
            }
        }
    }
    s = next_matrix; 
}

void Simulation::streaming() {

    Matrix next_matrix = s;
    vector<Cell*> neigh;
    vector<int> info;

    for (int i = 1; i < s.get_rows_num() - 1; i++) {
        for (int j = 1; j < s.get_columns_num() - 1; j++) {
            Cell& current_cell = s.get_element(i, j);
            neigh = s.get_neighbours(i, j);
            info = current_cell.get_info();;


            if (info[0] == 1 && j - 1 >= 0) {
                if (s.get_element(i, j - 1).get_color() != 122) {
                    next_matrix.get_element(i, j - 1).set_info({ 1, 0, 0, 0 });
                    next_matrix.get_element(i, j - 1).set_color(0);
                    next_matrix.get_element(i, j).set_color(255);
                    next_matrix.get_element(i, j).set_info({ 0,0,0,0 });
                }
                else {
                    next_matrix.get_element(i, j).set_info({ 0, 0, 1, 0 });
                    next_matrix.get_element(i, j).set_color(0);
                }
            }
            if (info[1] == 1 && i - 1 >= 0) {
                if (s.get_element(i - 1, j).get_color() != 122) {
                    next_matrix.get_element(i - 1, j).set_info({ 0, 1, 0, 0 });
                    next_matrix.get_element(i - 1, j).set_color(0);
                    next_matrix.get_element(i, j).set_color(255);
                    next_matrix.get_element(i, j).set_info({ 0,0,0,0 });
                }
                else {
                    next_matrix.get_element(i, j).set_info({ 0, 0, 0, 1 });
                    next_matrix.get_element(i, j).set_color(0);
                }
            }
            if (info[2] == 1 && j + 1 < s.get_columns_num()) {

                if (s.get_element(i, j + 1).get_color() != 122) {
                    next_matrix.get_element(i, j + 1).set_info({ 0, 0, 1, 0 });
                    next_matrix.get_element(i, j + 1).set_color(0);
                    next_matrix.get_element(i, j).set_color(255);
                    next_matrix.get_element(i, j).set_info({ 0,0,0,0 });
                }
                else {
                    next_matrix.get_element(i, j).set_info({ 1, 0, 0, 0 });
                    next_matrix.get_element(i, j).set_color(0);
                }
            }
            if (info[3] == 1 && i + 1 < s.get_rows_num()) {

                if (s.get_element(i + 1, j).get_color() != 122) {
                    next_matrix.get_element(i + 1, j).set_info({ 0, 0, 0, 1 });
                    next_matrix.get_element(i + 1, j).set_color(0);
                    next_matrix.get_element(i, j).set_color(255);
                    next_matrix.get_element(i, j).set_info({ 0,0,0,0 });
                }
                else {
                    next_matrix.get_element(i, j).set_info({ 0, 1, 0, 0 });
                    next_matrix.get_element(i, j).set_color(0);
                }


            }
        }
    }


    std::cout << "iteracja\n";
    s = next_matrix;
}