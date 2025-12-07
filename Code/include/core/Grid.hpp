#pragma once

#include <vector>
#include <memory>

#include "Cell.hpp"

class IRule;
class ICellState;

class Grid {
public:
    Grid(int w, int h);

    int getH();
    int getW();

    Cell& getCell(int x, int y);

    int countAliveNeighbors(int x, int y);

    void computeNextState(IRule& rule);
    bool applyNextState();

private:
    int width;
    int height;
    std::vector<std::vector<Cell>> cells;
    std::vector<std::vector<std::unique_ptr<ICellState>>> nextState;
};
