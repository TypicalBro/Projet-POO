#pragma once

#include <memory>
#include "ICellState.hpp"

class AliveState : public ICellState {
public:
    ~AliveState() override = default;

    bool isAlive() override;
    std::unique_ptr<ICellState> clone() override;
};
