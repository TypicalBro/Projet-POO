#include <iostream>
#include <string>
#include <fstream>

#include "Game.hpp"
#include "ConwayRule.hpp"
#include "IView.hpp"
#include "Grid.hpp"
#include "Cell.hpp"

using namespace std;

// Vue minimale pour les tests : ne fait rien visuellement
class TestView : public IView {
public:
    void init(Grid& /*grid*/) override {}
    void render(Grid& /*grid*/) override {}

    // En mode test, on avance toujours d'une itération
    bool waitNextStep() override { 
        return true; 
    }
};

// Lit un fichier de grille et compare avec l'état courant de la Grid
bool compareGridWithFile(Grid& grid, string& expectedPath) {
    ifstream file(expectedPath);
    if (!file) {
        cerr << "Erreur : impossible d'ouvrir le fichier attendu " << expectedPath << endl;
        return false;
    }

    int expectedH = 0, expectedW = 0;
    file >> expectedH >> expectedW;

    int h = grid.getH();
    int w = grid.getW();

    if (h != expectedH || w != expectedW) {
        cerr << "Dimensions differentes : attendu (" << expectedH << "x" << expectedW
             << "), obtenu (" << h << "x" << w << ")\n";
        return false;
    }

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int v = 0;
            file >> v;
            bool expectedAlive = (v == 1);
            bool actualAlive = grid.getCell(x, y).isAlive();

            if (expectedAlive != actualAlive) {
                cerr << "Difference a la position (" << x << ", " << y << ") : "
                     << "attendu=" << expectedAlive << ", obtenu=" << actualAlive << "\n";
                return false;
            }
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Usage: game_test <fichier_seed> <fichier_image> <nb_iterations>\n";
        return 1;
    }

    string seedFile   = argv[1];  // fichier grille initiale
    string imageFile  = argv[2];  // fichier grille attendue
    int iterations    = stoi(argv[3]);

    ConwayRule rule;
    TestView view;
    Game game(rule, view, iterations);

    try {
        game.loadFromFile(seedFile);
    } catch (exception& e) {
        cerr << "Erreur lors du chargement du seed : " << e.what() << "\n";
        return 1;
    }

    // On exécute N itérations
    for (int i = 0; i < iterations; ++i) {
        game.step();
    }

    // Récupérer la grille finale
    Grid& finalGrid = game.getGrid();

    // Comparaison avec la grille "image"
    bool ok = compareGridWithFile(finalGrid, imageFile);

    if (ok) {
        cout << "TEST OK : la grille apres " << iterations 
             << " iterations correspond a l'image.\n";
        return 0;
    } else {
        cout << "TEST FAILED : la grille finale ne correspond pas a l'image.\n";
        return 2;
    }
}
