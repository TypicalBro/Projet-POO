#pragma once

#include <memory>

class Cell;
class ICellState;

class IRule {
public:
    virtual ~IRule() = default;

    // Même signature que dans ConwayRule.cpp
    virtual std::unique_ptr<ICellState> computeNextState(
        Cell& cell,
        int aliveNeighbors
    ) = 0;
};
