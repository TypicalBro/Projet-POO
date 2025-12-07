#pragma once

#include <SFML/Graphics.hpp>
#include "IView.hpp"
#include "Grid.hpp"

class SFMLView : public IView {
public:
    SFMLView(unsigned int cellSize = 20, unsigned int margin = 1);

    void init(Grid& grid) override;
    void render(Grid& grid) override;
    bool waitNextStep() override;

private:
    void handleEvents();

    // NOUVEAU : helpers pour clic & patterns
    bool getMouseGridCoords(int& gridX, int& gridY) const;
    void stampPatternFromFile(const std::string& filename, int originX, int originY);
    void stampRandomSoup(int originX, int originY, int width, int height, double density);

    sf::RenderWindow m_window;
    unsigned int m_cellSize;
    unsigned int m_margin;

    unsigned int m_minCellSize = 5;
    unsigned int m_maxCellSize = 60;

    int m_offsetXCells = 0;
    int m_offsetYCells = 0;

    bool m_paused = false;
    bool m_stepOnce = false;

    unsigned int m_delayMs     = 100;
    unsigned int m_minDelayMs  = 20;
    unsigned int m_maxDelayMs  = 1000;

    Grid* m_grid = nullptr;
};


