#include "Grid.hpp"
#include "IRule.hpp"
#include "ICellState.hpp"
#include "Cell.hpp"
#include "DeadState.hpp"


using namespace std;

Grid::Grid(int w, int h):width(w),height(h){
    // On crée une grille height x width de cellules
    cells.resize(height);
    for (int y = 0; y < height; ++y) {
        cells[y].reserve(width);
        for (int x = 0; x < width; ++x) {
            cells[y].emplace_back(
                x, 
                y,
                std::make_unique<DeadState>()  // toutes mortes au départ
            );
        }
    }

    // Préparation de nextState
    nextState.resize(height);
    for (int y = 0; y < height; ++y) {
        nextState[y].resize(width);
    }
}
int Grid::getH(){return height;}
int Grid::getW(){return width;}
Cell& Grid::getCell(int x, int y){return cells[y][x];}
int Grid::countAliveNeighbors(int x, int y){
    int count = 0;

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            // On ignore la cellule elle-même
            if (dx == 0 && dy == 0) continue;

            int nx = x + dx;
            int ny = y + dy;

            // Effet thorique de la grille
            if (nx < 0){
                nx += width;
            }
            else if (nx >= width){
                nx -= width;
            }
            if (ny < 0){
                ny += height;
            }
            else if (ny >= height){
                ny -= height;
            }

            if (getCell(nx, ny).isAlive()) {
                ++count;
            }
        }
    }

    return count;
}

void Grid::computeNextState(IRule& rule){
    nextState.resize(height);
    for (int i = 0; i < height; i++){
        nextState[i].resize(width);
    }
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j ++){
            Cell& cell = getCell(j, i);
            int neighbors = static_cast<unsigned int>(countAliveNeighbors(j , i));
            nextState[i][j] = rule.computeNextState(cell, neighbors);
        }
    }
}
bool Grid::applyNextState(){
    bool change = false;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j ++){
            if (cells[i][j].isAlive() != nextState[i][j]->isAlive()){
                cells[i][j].setState(move(nextState[i][j]));
                change = true;
            }
        }
    }
    return change;
}

