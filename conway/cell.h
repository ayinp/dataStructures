#ifndef CELL_H
#define CELL_H
#include <vector>
#include "vec2d.h"
#include "graphics.h"

class Cell
{
public:
    int width = 10;
    int height = 10;
    mssm::Color color = mssm::BLACK;
public:
    Cell();
    void draw(mssm::Graphics &g,  Vec2d location, bool alive);
};


#endif // CELL_H
