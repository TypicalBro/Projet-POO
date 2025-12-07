#include "ConwayRule.hpp"   //Declaration
#include "Cell.hpp"         //Lire l'etat actuel
#include "AliveState.hpp"   //Creer de nouveaux etats
#include "DeadState.hpp"    //--pareil--

using namespace std;

unique_ptr<ICellState> ConwayRule::computeNextState(Cell& cell, int aliveNeighbors){
    bool alive = cell.isAlive();
    if (alive){
        if (aliveNeighbors == 2 || aliveNeighbors == 3){
            return make_unique<AliveState>();
        }
        else{
            return make_unique<DeadState>();
        }
    }
    else{
        if (aliveNeighbors == 3){
            return make_unique<AliveState>();
        }
        else{
            return make_unique<DeadState>();
        }
    }
}


