#include <iostream>
#include <string>

#include "Game.hpp"
#include "ConwayRule.hpp"
#include "SFMLView.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: game_sfml <fichier_entree> [max_iterations]\n";
        return 1;
    }

    string inputFile = argv[1];
    unsigned int maxIterations = 200;
    if (argc >= 3) {
        maxIterations = static_cast<unsigned int>(stoi(argv[2]));
    }

    ConwayRule rule;
    SFMLView view(20, 1);   // taille des cellules + marge
    Game game(rule, view, maxIterations);

    try {
        game.loadFromFile(inputFile);
    } catch (const exception& e) {
        cerr << "Erreur lors du chargement : " << e.what() << "\n";
        return 1;
    }

    game.run();

    return 0;
}
