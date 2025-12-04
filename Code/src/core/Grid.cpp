#include "Grid.hpp"
#include "IRule.hpp"

using namespace std;

Grid::Grid(int w, int h):width(w),height(h){
    vector<Cell> temp2;
    for (int i = 0; i < width; i++){
        temp2.push_back(unique_ptr<ICellState>);
    }
    vector<vector<Cell>> temp(h, temp2);
}
int Grid::getH(){return height;}
int Grid::getW(){return width;}
Cell& Grid::getCell(int x, int y){return cells[y][x];}
int Grid::countAliveNeighbors(int x, int y){
    int count = 0;
    if (x == 0){
        if (y == 0){
            if (getCell(x+1,y).isAlive()){count ++;}
            if (getCell(x,y+1).isAlive()){count ++;}
            if (getCell(x+1,y+1).isAlive()){count ++;}
        }
        else if (y == cells[0].size() - 1){
            if (getCell(x+1,y).isAlive()){count ++;}
            if (getCell(x,y-1).isAlive()){count ++;}
            if (getCell(x+1,y-1).isAlive()){count ++;}
        }
        else{
            if (getCell(x+1,y).isAlive()){count ++;}
            if (getCell(x,y+1).isAlive()){count ++;}
            if (getCell(x+1,y+1).isAlive()){count ++;}
            if (getCell(x,y-1).isAlive()){count ++;}
            if (getCell(x+1,y-1).isAlive()){count ++;}
        }
    }
    else if (x == cells.size()-1){
        if (y == 0){
            if (getCell(x-1,y).isAlive()){count ++;}
            if (getCell(x,y+1).isAlive()){count ++;}
            if (getCell(x-1,y+1).isAlive()){count ++;}
        }
        else if (y == cells[0].size() - 1){
            if (getCell(x-1,y).isAlive()){count ++;}
            if (getCell(x,y-1).isAlive()){count ++;}
            if (getCell(x-1,y-1).isAlive()){count ++;}
        }
        else{
            if (getCell(x-1,y).isAlive()){count ++;}
            if (getCell(x,y+1).isAlive()){count ++;}
            if (getCell(x-1,y+1).isAlive()){count ++;}
            if (getCell(x,y-1).isAlive()){count ++;}
            if (getCell(x-1,y-1).isAlive()){count ++;}
        }
    }
    else {
        if (y == 0){
            if (getCell(x-1,y).isAlive()){count ++;}
            if (getCell(x+1,y).isAlive()){count ++;}
            if (getCell(x,y+1).isAlive()){count ++;}
            if (getCell(x+1,y+1).isAlive()){count ++;}
            if (getCell(x-1,y+1).isAlive()){count ++;}
        }
        else if (y == cells[0].size() - 1){
            if (getCell(x-1,y).isAlive()){count ++;}
            if (getCell(x+1,y).isAlive()){count ++;}
            if (getCell(x,y-1).isAlive()){count ++;}
            if (getCell(x+1,y+1).isAlive()){count ++;}
            if (getCell(x-1,y-1).isAlive()){count ++;}
        }
        else{
            for (int i = -1; i < 2; i++){
                for (int j = -1; j < 2; j++){
                    if (getCell(x+j,y+i).isAlive() && !(i == 0 && j == 0)){count ++;}
                }
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
            int neighbors = countAliveNeighbors(j , i)
            nextState[i][j] = rule.computeNextState(cell, neighbors)
        }
    }
}
bool Grid::applyNextState(){
    bool change = false;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j ++){
            if (cells[i][j].isAlive != nextState[i][j].isAlive){
                cells[i][j].setState(move(nextState[i][j]));
                change = true;
            }
        }
    }
}

