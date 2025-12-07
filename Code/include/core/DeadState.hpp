#pragma once

#include <memory>
#include "ICellState.hpp"

class DeadState : public ICellState {
public:
    ~DeadState() override = default;

    bool isAlive() override;
    std::unique_ptr<ICellState> clone() override;
};
