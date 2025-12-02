#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <vector>
#include "Regles.cpp"


using namespace std;

class Jeu{
    protected:
    bool mode_graphique;
    int nb_iterations;
    public:
    Jeu(bool mode_g):mode_graphique(mode_g),nb_iterations(0){}
    void demarrer_simulation(){}
    void creation_fichier_sortie(){}
};

class Grille : public Jeu{
    
    protected:

    int largeur;
    int hauteur;
    unordered_map<int[2], Jeu&> grid;

    public:

    void charger_fichier_entree(){
        ifstream fichier("grid.txt");
        string ligne;
        vector<int> num;
        int n_ligne = 0;
        while (getline(fichier, ligne)){
            if (n_ligne == 0){
                bool first = true;
                for (int i = 0;i < fichier.size();i++){
                    if (ligne[i] != " "){
                        num.push_back(ligne[i].toint());
                    }
                    else{
                        if (first) {
                            first = false;
                            for(int j = num.size();j>=0;j--){
                                largeur += num[num.size()-j]*10**j;
                            }
                        }
                        else{
                            for(int j = num.size();j>=0;j--){
                                hauteur += num[num.size()-j]*10**j;
                            }
                        }
                        while (!num.empty()){
                            num.pop_back();
                        }
                    }
                }
            }
            n_ligne++;
            else{
                for (int i = 0;i < ligne.size();i++2){
                    if (ligne[i] == "1"){
                        Cellule cell(true);
                        grid[[i/2,n_ligne]] = &cell;
                    }
                }
            }
        }
        fichier.close();
    }

    int[2] obtenir_voisins(int[2] coord){
        for (int y = -1; y < 2; y++){
            for (int x = -1; x < 2; x++){
                if (grid[[coord[0] + x, coord[1] + y]]){}
                else{
                    Cellule cell(false);
                    grid[[coord[0] + x, coord[1] + y]] = &cell;
                }
            }
        }
    }
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


