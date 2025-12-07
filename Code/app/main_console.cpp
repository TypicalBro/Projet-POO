#include <iostream>
#include <string>

#include "Game.hpp"
#include "ConwayRule.hpp"
#include "ConsoleView.hpp"

using namespace std;

static std::string computeOutputDir(const std::string& inputPath) {
    // on enlève le chemin
    std::string base = inputPath;
    auto posSlash = base.find_last_of("/\\");
    if (posSlash != std::string::npos) {
        base = base.substr(posSlash + 1);
    }
    // on enlève l'extension
    auto posDot = base.find_last_of('.');
    if (posDot != std::string::npos) {
        base = base.substr(0, posDot);
    }
    // <nom_du_fichier_dentree>_out
    return base + "_out";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: game_console <fichier_entree> [max_iterations]\n";
        return 1;
    }

    string inputFile = argv[1];
    unsigned int maxIterations = 100;
    if (argc >= 3) {
        maxIterations = static_cast<unsigned int>(stoi(argv[2]));
    }

    std::string outDir = computeOutputDir(inputFile);

    ConwayRule rule;
    ConsoleView view(outDir);
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
