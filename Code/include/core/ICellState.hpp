#pragma once //Protection contre les appels recursifs

#include <memory> //Pour eviter les fuites de memoire

using namespace std;

class ICellState{
    public:

    //Renvoit True si la cellule est vivante
    virtual bool isAlive();

    //Dupliquer la cellule sans passer par new/delete grace a unique_ptr
    virtual unique_ptr<ICellState> clone();
};