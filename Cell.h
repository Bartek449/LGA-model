#pragma once
#include <vector>
#include <random>


class Cell {
private:
    int color;
    int population;
    char direction;
    
public:
    Cell();
    Cell(int,int,char);
    int get_color();
    void set_color(int);
    int get_population();
    void set_population(int);
    char get_direction();
    void set_direction(char);
    
};