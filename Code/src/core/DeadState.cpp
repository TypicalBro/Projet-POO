#include "DeadState.hpp"

using namespace std;

bool DeadState::isAlive(){return false;}

unique_ptr<ICellState> DeadState::clone(){
    unique_ptr<ICellState> temp = make_unique<DeadState>(*this);
    return temp;
}
