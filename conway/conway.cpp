#include "conway.h"
#include<iostream>
#include<functional>
using namespace mssm;
using namespace std;

Conway::Conway(int height, int width)
    :height{height}, width{width}, rule(512)
{
    for(int i = 0; i < rule.size(); i++){
        rule[i] = rand()%2;
    }
}

void Conway::draw(Graphics &g)
{
    Cell example(false);
    int w = example.width;
    int h = example.height;

    int xStart = (g.width()-w*width)/2;
    int yStart = (g.height()-h*height)/2;

    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            Vec2d location = {xStart + w*i,yStart + h*j};
            cells[j][i].draw(g, location);
        }
    }
}

void Conway::create(function<bool(double)> randomTrue)
{
    cells.resize(height);
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            cells[j].push_back(Cell(randomTrue(0.2)));
        }
    }
}

int Conway::numNeighbors(int j, int i)
{
    int num = 0;
    if(j > 0 && cells[j-1][i].alive){
        num++;
    }
    if(j > 0 && i > 1 && cells[j-1][i-1].alive){
        num++;
    }
    if(j > 0 && i < width-1 && cells[j-1][i+1].alive){
        num++;
    }
    if(i > 0 && cells[j][i-1].alive){
        num++;
    }
    if(i < width-1 && cells[j][i+1].alive){
        num++;
    }
    if(j < height-1 && cells[j+1][i].alive){
        num++;
    }
    if(j < height-1 && i > 1 && cells[j+1][i-1].alive){
        num++;
    }
    if(j < height-1 && i < width-1 && cells[j+1][i+1].alive){
        num++;
    }
    return num;
}

void Conway::update()
{
    vector<vector<Cell>> newCells = cells;
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            newCells[j][i].alive = cellAlive2(j, i);
        }
    }
    cells = newCells;
}

bool Conway::cellAlive(int j, int i)
{
    if(cells[j][i].alive){
        if(numNeighbors(j, i) == 2 || numNeighbors(j, i) == 3){
            return true;
        }
        return false;
    }
    if(numNeighbors(j, i) == 3){
        return true;
    }
    return false;
}

bool Conway::cellAlive2(int j, int i)
{
    int number;
    number = checkAlive(j,i) + 2*checkAlive(j-1,i) + 4*checkAlive(j+1,i) + 8*checkAlive(j,i-1) + 16*checkAlive(j,i+1)
            + 32*checkAlive(j-1,i-1) + 64*checkAlive(j+1,i+1) + 128*checkAlive(j-1,i+1) + 256*checkAlive(j+1,i-1);
    return rule[number];
}

void Conway::messWithCell(Graphics& g, Vec2d mouseLocation)
{
    int w = cells[0][0].width;
    int h = cells[0][0].height;

    int xS = (g.width()-w*width)/2;
    int yS = (g.height()-h*height)/2;

    int j = (mouseLocation.y-yS)/h;
    int i = (mouseLocation.x-xS)/w;

    if(cells[j][i].alive){
        cells[j][i].alive = false;
    }
    else{
        cells[j][i].alive = true;
    }
}

bool Conway::checkAlive(int j, int i)
{
    if(j < 0 || j >= height || i < 0 || i >= width){
        return false;
    }
    return cells[j][i].alive;
}

void Conway::generateRule()
{
    for(int i = 0; i < rule.size(); i++){
        rule[i] = rand()%2;
    }
}

void Conway::clear()
{
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            cells[j][i].alive = false;
        }
    }
}

void Conway::regenGuys()
{
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            cells[j][i].alive = rand()%2;
        }
    }
}







