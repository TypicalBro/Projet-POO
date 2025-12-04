#include "Cell.hpp"

using namespace std;

Cell::Cell(unsigned int x, unsigned int y, std::unique_ptr<ICellState> initialState):x(x),y(y),state(move(initialState)){}
int Cell::getx(){return x;}
int Cell::gety(){return y;}
bool isAlive(){return state->isAlive();}
ICellState& getState(){return state;}
void setState(unique_ptr<ICellState> newState){state = move(newState)}
