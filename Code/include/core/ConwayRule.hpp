#pragma once
#include <memory>
#include "IRule.hpp"

using namespace std;

class ICellState;

class ConwayRule : public IRule {
    public: 
    unique_ptr<ICellState> computeNextState(Cell& cell, int aliveNeighbors)override;
}