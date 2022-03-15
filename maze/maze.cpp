#include "maze.h"
using namespace mssm;
using namespace std;

Maze::Maze(int height, int width)
    :height{height}, width{width}
{

}

void Maze::draw(Graphics &g)
{
    Cell example({0,0,0,0});
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

void Maze::create(Graphics &g)
{
    double percentWall = 0.3;
    cells.resize(height);
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            if(j == 0 && i == 0){
                cells[j].push_back(Cell({1,1,g.randomTrue(percentWall),g.randomTrue(percentWall)}));
            }
            else if(j == 0 && i == width-1){
                cells[j].push_back(Cell({1,g.randomTrue(percentWall),1,g.randomTrue(percentWall)}));
            }
            else if(j == height-1 && i == 0){
                cells[j].push_back(Cell({g.randomTrue(percentWall),1,g.randomTrue(percentWall),1}));
            }
            else if(j == height-1 && i == height-1){
                cells[j].push_back(Cell({g.randomTrue(percentWall),g.randomTrue(percentWall),1,1}));
            }
            else if(j == 0){
                cells[j].push_back(Cell({1,g.randomTrue(percentWall),g.randomTrue(percentWall),g.randomTrue(percentWall)}));
            }
            else if(j == height-1){
                cells[j].push_back(Cell({g.randomTrue(percentWall),g.randomTrue(percentWall),g.randomTrue(percentWall),1}));
            }
            else if(i == 0){
                cells[j].push_back(Cell({g.randomTrue(percentWall),1,g.randomTrue(percentWall),g.randomTrue(percentWall)}));
            }
            else if(i == width-1){
                cells[j].push_back(Cell({g.randomTrue(percentWall),g.randomTrue(percentWall),1,g.randomTrue(percentWall)}));
            }
            else{
                cells[j].push_back(Cell({g.randomTrue(percentWall),g.randomTrue(percentWall),g.randomTrue(percentWall),g.randomTrue(percentWall)}));
            }
        }
    }
}

