#include "Cell.hpp"

using namespace std;

Cell::Cell(int x, int y, unique_ptr<ICellState> initialState):x(x),y(y),state(move(initialState)){}
int Cell::getx(){return x;}
int Cell::gety(){return y;}
bool Cell::isAlive(){return state->isAlive();}
ICellState& Cell::getState(){return *state;}
void Cell::setState(unique_ptr<ICellState> newState){state = move(newState);}
