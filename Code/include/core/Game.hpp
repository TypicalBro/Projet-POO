#pragma once
#include <memory>
#include <string>
#include "Grid.hpp"
#include "IRule.hpp"
#include "IView.hpp"

using namespace std;

class Game{
    private:
    unique_ptr<Grid> grid;
    IRule& rule;
    IView& view
    int max_it;
    int current_it;
    bool stable;
    public:
    Game(IRule& rule, IView& view, int max_it);
    void loadFromFile(string& path);
    void run();
    void step();
    bool isStable();
}