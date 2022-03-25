#include "maze.h"
using namespace mssm;
using namespace std;

Maze::Maze(int height, int width)
    :height{height}, width{width}
{

}

void Maze::draw(Graphics &g)
{
    Cell example;
    int w = example.width;
    int h = example.height;
    int xStart = (g.width()-w*width)/2;
    int yStart = (g.height()-h*height)/2;

    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            Vec2d location = {xStart + w*i,yStart + h*j};
            cells[j][i].draw(g, location, true);
        }
    }
}

void Maze::create(Graphics &g)
{
    Cell cell;
    cells.resize(height);
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            if(j == 0 && i == 0){
                cells[j].push_back(cell);
            }
            else if(j == 0 && i == width-1){
                cells[j].push_back(cell);
            }
            else if(j == height-1 && i == 0){
                cells[j].push_back(cell);
            }
            else if(j == height-1 && i == height-1){
                cells[j].push_back(cell);
            }
            else if(j == 0){
                cells[j].push_back(cell);
            }
            else if(j == height-1){
                cells[j].push_back(cell);
            }
            else if(i == 0){
                cells[j].push_back(cell);
            }
            else if(i == width-1){
                cells[j].push_back(cell);
            }
            else{
                cells[j].push_back(cell);
            }
        }
    }
}

