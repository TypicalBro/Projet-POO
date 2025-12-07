#pragma once

#include <memory>
#include "ICellState.hpp"

class Cell {
public:
    Cell(int x, int y, std::unique_ptr<ICellState> initialState);

    int getx();
    int gety();

    bool isAlive();

    ICellState& getState();
    void setState(std::unique_ptr<ICellState> newState);

private:
    int x;
    int y;
    std::unique_ptr<ICellState> state;
};
