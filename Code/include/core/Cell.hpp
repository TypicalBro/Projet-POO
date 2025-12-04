#pragma once
#include "ICellState.hpp"

using namespace std;

class Cell{
    private:
    int x;
    int y;

    unique_ptr<ICellState> state;

    public:
    Cell(int x, int y, unique_ptr<ICellState> state);
    int getx();
    int gety();
    bool isAlive();
    const ICellState& getState();
    void setState(unique_ptr<ICellState> state);
};
