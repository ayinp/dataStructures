#include <iostream>
#include "graphics.h"
#include "cell.h"
#include "maze.h"

using namespace std;
using namespace mssm;

#pragma GCC diagnostic ignored "-Wsign-compare"

int main()
{
    Graphics g("Test", 1024, 768);

//    Cell all({1,1,1,1}, {100, 100});
//    Cell noT({0,1,1,1}, {100, 200});
//    Cell noB({1,1,1,0}, {100, 300});
//    Cell noL({1,0,1,1}, {100, 400});
//    Cell noR({1,1,0,1}, {100, 500});
//    Cell ThruU({0,1,1,0}, {100, 600});
//    Cell ThruR({1,0,0,1}, {200, 100});
//    Cell cornerTL({1,1,0,0}, {200, 200});
//    Cell cornerTR({1,0,1,0}, {200, 300});
//    Cell cornerBL({0,1,0,1}, {200, 400});
//    Cell cornerBR({0,0,1,1}, {200, 500});
//    Cell none({0,0,0,0}, {200, 600});

    Maze maze(20, 20);
    maze.create(g);
    while (g.draw()) {
        maze.draw(g);
//        all.draw(g);
//        noT.draw(g);
//        noB.draw(g);
//        noL.draw(g);
//        noR.draw(g);
//        ThruU.draw(g);
//        ThruR.draw(g);
//        cornerTL.draw(g);
//        cornerTR.draw(g);
//        cornerBL.draw(g);
//        cornerBR.draw(g);
//        none.draw(g);





        for (const Event& e : g.events()) {
            switch (e.evtType) {
            case EvtType::KeyPress:
                if (e.arg == ' ') {

                }
                break;
            default:
                break;
            }
        }
    }

    return 0;
}


