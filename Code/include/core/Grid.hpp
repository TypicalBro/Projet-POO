#pragma once
#include <vector>
#include <memory>
#include "Cell.hpp"

using namespace std;

class IRule;

class Grid{
    int width;
    int height;
    vectir<vector<Cell>>> cell;
    vector<vector<unique_ptr<ICellState>>> nextState;
}