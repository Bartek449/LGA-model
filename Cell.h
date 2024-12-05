#pragma once
#include<iostream>
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

    void set_color(int);
    void set_info(vector<int>);
    
    int get_color() const;
    vector<int> get_info() const;
    
    bool is_empty() const;
    bool is_wall() const;
    bool is_gas() const;
};