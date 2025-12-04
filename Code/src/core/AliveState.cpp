#include "AliveState.hpp"

using namespace std;

bool AliveState::isAlive(){return true}
unique_ptr<ICellState> AliveState::clone(){
    unique_ptr<ICellState> temp = make_unique<AliveState>(*this);
    return temp;
}