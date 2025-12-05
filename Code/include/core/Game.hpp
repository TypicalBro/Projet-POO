#pragma once

#include <memory>
#include <string>

#include "Grid.hpp"
#include "IRule.hpp"
#include "IView.hpp"

class Game {
public:
    Game(IRule& rule, IView& view, int maxIterations);

    void loadFromFile(std::string& path);
    void step();
    void run();
    Grid& getGrid();


private:
    std::unique_ptr<Grid> grid;
    IRule& rule;
    IView& view;

    int max_it;
    int current_it;
    bool stable;
    bool view_init;
};
