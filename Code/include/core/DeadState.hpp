#pragma once
#include <memory>
#include "ICellState.hpp"

using namespace std;

class AliveState : public ICellState{
    bool isAlive() override;
    unique_ptr<ICellState> clone() override;
}