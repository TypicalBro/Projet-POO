#pragma once

#include <memory>

class ICellState {
public:
    virtual ~ICellState() = default;

    // Non-const pour coller à tes implémentations existantes
    virtual bool isAlive() = 0;
    virtual std::unique_ptr<ICellState> clone() = 0;
};
