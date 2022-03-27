#include <iostream>
#include "graphics.h"
#include "cell.h"
#include "conway.h"

using namespace std;
using namespace mssm;

#pragma GCC diagnostic ignored "-Wsign-compare"

int main()
{
    Graphics g("Test", 1024, 768);

    Conway maze(30, 30);
    maze.create([&g](double pct){return g.randomTrue(pct);}); // this is a lambda/anonomous function. He creates a closure
    //which is a function along with some data -- makes a class. square braket things are feilds, body becomes the body of
    //a method on the class and now has access to those data bits. Things in square brakets are captures bc we steal to use
    //in our new function.
    while (g.draw()) {
        maze.draw(g);
        maze.update();




        for (const Event& e : g.events()) {
            cout<< e<< endl;
            switch (e.evtType) {
            case EvtType::MousePress:
                maze.messWithCell(g, {e.x, e.y});
                break;
            default:
                break;
            }
        }
    }

    return 0;
}


