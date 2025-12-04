#pragma once //Protection contre les appels recursifs

#include <memory> //Pour eviter les fuites de memoire

using namespace std;

class ICellState{
    public:
    virtual bool isAlive();
    virtual unique_ptr<ICellState> clone();
};