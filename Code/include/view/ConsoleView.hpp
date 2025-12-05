#pragma once

#include <string>
#include "IView.hpp"

class Grid;

class ConsoleView : public IView {
public:
    // Constructeur avec le nom du dossier de sortie
    explicit ConsoleView(const std::string& outputDir);

    void init(Grid& grid) override;
    void render(Grid& grid) override;
    bool waitNextStep() override;

private:
    std::string m_outputDir;
    int m_iteration = 0;
};
