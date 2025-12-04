#pragma once


class Grid;

class IView{
    virtual void init(Grid& grid) = 0;
    virtual void render(Grid& grid) = 0;
    virtual void waitNextStep() = 0;

    virtual ~IView();
}