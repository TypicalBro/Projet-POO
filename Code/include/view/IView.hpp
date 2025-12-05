#pragma once

class Grid;

class IView {
public:
    virtual ~IView() = default;

    virtual void init(Grid& grid) = 0;
    virtual void render(Grid& grid) = 0;
    virtual bool waitNextStep() = 0;
};
