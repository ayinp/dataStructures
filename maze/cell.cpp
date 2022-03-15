#include "cell.h"
using namespace std;
using namespace mssm;

Cell::Cell(std::vector<bool> walls)
    :walls{walls}
{

}

void Cell::draw(Graphics& g, Vec2d location)
{
    if(walls[0]){ //top
        g.line(location, {location.x + width, location.y}, WHITE);
    }
    if(walls[1]){ //left
        g.line(location, {location.x, location.y + height}, WHITE);
    }
    if(walls[2]){//right
        g.line({location.x + width, location.y}, {location.x + width, location.y + width}, WHITE);
    }
    if(walls[3]){//bottom
        g.line({location.x, location.y + height}, {location.x + width, location.y + width}, WHITE);
    }
}
