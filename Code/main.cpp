#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <map>
#include "Jeu.cpp"
#include "Regles.cpp"
#include "HUD.cpp"
#include "Init.cpp"

using namespace std;

int main(){


    return 0;
}




#include <iostream>
#include <unordered_map>

using namespace std;



class Jeu{
    protected:
    bool mode_graphique;
    int nb_iterations;
    public:
    void charger_fichier_entree(){}
    void demarrer_simulation(){}
    void creation_fichier_sortie(){}
};

class Grille : public Jeu{
    protected:
    int largeur;
    int hauteur;
    unordered_map<int[2], Jeu&> grid;
    public:
    void init(){}
    int[2] obtenir_voisins(int[2]){}
    int nombre_voisins_vivants(int[2]){}
    void update()
};

class Cellule : public Jeu{
    protected:
    bool ProchainEtat;
    bool EtatCellule;
    int x;
    int y;
    public:
    bool est_vivante(){}
    void calcul_etat(bool regle){}
};

class Regle_Jeu{
    public:
    Regle_1(int nb_voisins){}
    Regle_2(int nb_voisins){}
};

class HUD{
    public:
    void affichage_graphique()
    void affichage_console()

};


