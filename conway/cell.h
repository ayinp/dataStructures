#ifndef CELL_H
#define CELL_H
#include <vector>
#include "vec2d.h"
#include "graphics.h"

class Cell
{
public:
    int width = 20;
    int height = 20;
    bool alive = false;
    mssm::Color color = mssm::BLACK;
public:
    Cell(bool alive);
    void draw(mssm::Graphics &g,  Vec2d location);
};


#endif // CELL_H
