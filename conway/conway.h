#ifndef CONWAY_H
#define CONWAY_H
#include<vector>
#include<functional>
#include "cell.h"
#include "graphics.h"


class Conway
{
public:
    int height;
    int width;
    std::vector<std::vector<Cell>> cells;
    std::vector<bool> rule;
public:
    Conway(int height, int width);
    void draw(mssm::Graphics &g);
    void create(std::function<bool (double)> randomTrue);
    int numNeighbors(int j, int i);
    void update();
    bool cellAlive(int j, int i);
    bool cellAlive2(int j, int i);
    void messWithCell(mssm::Graphics &g, Vec2d mouseLocation);
    bool checkAlive(int i, int j);
    void generateRule();
    void clear();
    void regenGuys();
};

#endif // CONWAY_H
