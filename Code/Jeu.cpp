#include "Jeu.hpp"
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
    friend class Regle_Jeu; // Permet à la classe Regle_Jeu de modifier les attributs de la classe Cellule
    protected:
    bool ProchainEtat;
    bool EtatCellule;
    int x;
    int y;
    public:
    bool est_vivante(){}
    void calcul_etat(bool regle){}
};