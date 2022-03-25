#include "cell.h"
using namespace std;
using namespace mssm;

Cell::Cell()
{

}

void Cell::draw(Graphics& g, Vec2d location, bool alive)
{
    if(alive){
        color = WHITE;
    }
    else{
        color = BLACK;
    }
    g.rect(location, width, height, RED, color);
}
