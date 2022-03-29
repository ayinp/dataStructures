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
    srand(time(0));
    Conway maze(75, 75);
    bool update = true;
    maze.create([&g](double pct){return g.randomTrue(pct);}); // this is a lambda/anonomous function. He creates a closure
    //which is a function along with some data -- makes a class. square braket things are feilds, body becomes the body of
    //a method on the class and now has access to those data bits. Things in square brakets are captures bc we steal to use
    //in our new function.
    while (g.draw()) {
        maze.draw(g);
        if(update){
            maze.update();
        }




        for (const Event& e : g.events()) {
            cout<< e<< endl;
            switch (e.evtType) {
            case EvtType::MouseMove:
                maze.messWithCell(g, g.mousePos());
                break;
            case EvtType::MousePress:
                maze.messWithCell(g, g.mousePos());
                break;
            case EvtType::KeyPress:
                if(e.arg == 'R'){
                    maze.generateRule();
                }
                if(e.arg == ' '){
                    if(update){
                        update = false;
                    }
                    else{
                        update = true;
                    }
                }
                if(e.arg == 'C'){
                    maze.clear();
                }
                if(!update && e.arg == 'P'){
                    maze.update();
                }
                if(e.arg == 'G'){
                    maze.regenGuys();
                }
                break;

            default:
                break;
            }
        }
    }

    return 0;
}


