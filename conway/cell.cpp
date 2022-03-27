#include "cell.h"
using namespace std;
using namespace mssm;

Cell::Cell(bool alive)
    :alive{alive}
{

}

void Cell::draw(Graphics& g, Vec2d location)
{
    if(alive){
        color = WHITE;
    }
    else{
        color = BLACK;
    }
    g.rect(location, width, height, RED, color);
}
