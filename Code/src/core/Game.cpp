#include <fstream>
#include "Game.hpp"
#include "AliveState.hpp"
#include "DeadState.hpp"


using namespace std;

Game::Game(IRule& rule, IView& view, int maxIterations): 
grid(nullptr),rule(rule),view(view),max_it(maxIterations),current_it(0),stable(false),view_init(false){}

Grid& Game::getGrid(){
    return *grid;
}

void Game::loadFromFile(string& path) {
    ifstream file(path);
    if (!file) {
        throw runtime_error("Impossible d'ouvrir le fichier : " + path);
    }

    int h = 0;
    int w = 0;
    file >> h >> w;

    // Création de la grille
    grid = make_unique<Grid>(w, h);

    // Lire la grille ligne par ligne
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int value;
            file >> value;

            if (value == 1) {
                // cellule vivante
                grid->getCell(x, y).setState(make_unique<AliveState>());
            } else {
                // cellule morte
                grid->getCell(x, y).setState(make_unique<DeadState>());
            }
        }
    }


    current_it = 0;
    stable = false;
    view_init = false;
}

void Game::step (){
    if (grid->getW() == 0){
        return;
    }
    else if (grid->getH() == 0){
        return;
    }
    grid->computeNextState(rule);
    stable = !grid->applyNextState();
    current_it++;
}
void Game::run(){
    if (grid->getW() == 0){
        return;
    }
    else if (grid->getH() == 0){
        return;
    }
    view.init(*grid);
    view_init = true;
    while (!stable && current_it < max_it) {
        view.render(*grid);

        // Demander à la vue si on doit avancer le temps ou rester (pause)
        if (!view.waitNextStep()) {
            continue;   // ne pas appeler step(), on reste sur cette génération
        }

        step();
    }

}


