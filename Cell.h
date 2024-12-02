#pragma once
#include <vector>
#include <random>

using namespace std;

class Cell {
private:
    int color;
    vector <int> info;
    
public:
    Cell();
    Cell(int,vector<int>);
    int get_color();
    void set_color(int);
    vector<int> get_info();
    void set_info(vector<int>);
    
};