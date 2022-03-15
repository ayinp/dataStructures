#ifndef CELL_H
#define CELL_H
#include <vector>
#include "vec2d.h"
#include "graphics.h"

class Cell
{
public:
    std::vector<bool> walls = {false, false, false, false}; // true = wall, index 0 = top, 1 = left, 2 = right, 3 = bottom
    int width = 50;
    int height = 50;
public:
    Cell(std::vector<bool> walls);
    void draw(mssm::Graphics &g,  Vec2d location);
};


#endif // CELL_H
