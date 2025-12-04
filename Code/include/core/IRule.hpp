#pragma once //Protection contre les appels recursifs

#include <memory> //Pour eviter les fuites de memoire

using namespace std;

class Cell;         //Forward calling
class ICellState;   //permet d'eviter les includes inutiles / circulaires
                    //Faisable car nous avons seulement besoin des pointeurs des objets 

class IRule {
    public:
    virtual unique_ptr<ICellState> computeNextState(
        const Cell& cell
        unsigned int alive Neighbors
    )
};