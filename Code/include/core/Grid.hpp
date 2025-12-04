#pragma once
#include <vector>
#include <memory>
#include "Cell.hpp"

using namespace std;

class IRule;

class Grid{
    private:
    int width;
    int height;
    vectir<vector<Cell>>> cells;
    vector<vector<unique_ptr<ICellState>>> nextState;
    public:
    Grid(int width,int height);
    int getW();
    int getH();
    Cell& getCell(int x, int y);
    int countAliveNeighbors(int x, int y);
    void computeNextState(IRule rule);
    bool applyNextState();

}