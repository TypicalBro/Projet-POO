#pragma once

#include "IRule.hpp"

class ConwayRule : public IRule {
public:
    ~ConwayRule() override = default;

    std::unique_ptr<ICellState> computeNextState(
        Cell& cell,
        int aliveNeighbors
    ) override;
};
