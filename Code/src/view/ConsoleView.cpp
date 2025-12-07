#include "ConsoleView.hpp"
#include "Grid.hpp"
#include "Cell.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

ConsoleView::ConsoleView(const std::string& outputDir)
    : m_outputDir(outputDir) {}

void ConsoleView::init(Grid& grid){
    // Crée le dossier <nom_fichier>_out s'il n'existe pas
    if (!fs::exists(m_outputDir)) {
        fs::create_directories(m_outputDir);
    }

    cout << "Mode console : ecriture des grilles dans le dossier \""
         << m_outputDir << "\"\n";
    (void)grid; // pas encore utilisé ici
}

void ConsoleView::render(Grid& grid){
    int h = grid.getH();
    int w = grid.getW();

    // --- Affichage dans la console (optionnel) ---
    cout << "Iteration " << m_iteration << " :" << endl;
    for (int i = 0; i < h; i++){
        cout << "|";
        for (int j = 0; j < w; j++){
            if (grid.getCell(j, i).isAlive()){
                cout << "#";
            } else {
                cout << " ";
            }
            cout << "|";
        }
        cout << "\n";
    }
    cout << endl;

    // --- Ecriture dans un fichier pour correction ---
    // Nom du fichier : iter_<n>.txt
    std::string filename = m_outputDir + "/iter_" + std::to_string(m_iteration) + ".txt";
    std::ofstream out(filename);
    if (!out) {
        cerr << "Erreur : impossible d'ouvrir le fichier de sortie " << filename << endl;
        return;
    }

    // Première ligne : hauteur largeur
    out << h << " " << w << "\n";

    // Matrice de 0/1
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            int v = grid.getCell(j, i).isAlive() ? 1 : 0;
            out << v;
            if (j < w - 1) out << " ";
        }
        out << "\n";
    }

    ++m_iteration;
}

bool ConsoleView::waitNextStep() {
    // En mode console "batch", on ne met pas de pause :
    // on avance toujours à l'iteration suivante.
    return true;
}
