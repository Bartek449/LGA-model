#pragma once
#include<iostream>
#include <vector>
#include <random>

#define EMPTY vector<int>{0,0,0,0}
#define WALL vector<int>{-1,-1,-1,-1}

using namespace std;

class Cell {
private:
    vector <int> info;
public:
    Cell();
    Cell(int, vector<int>);

    void set_info(vector<int>);
    void set_direct_info(int, int);
    vector<int> get_info();

};