#ifndef MAZE_H
#define MAZE_H
#include<vector>
#include "cell.h"
#include "graphics.h"

class Maze
{
public:
    int height;
    int width;
    std::vector<std::vector<Cell>> cells;
public:
    Maze(int height, int width);
    void draw(mssm::Graphics &g);
    void create(mssm::Graphics &g);
};

#endif // MAZE_H
