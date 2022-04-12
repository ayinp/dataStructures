#include <iostream>
#include "graphics.h"

using namespace std;
using namespace mssm;

#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif

// Note:  Mac Users who are using Qt Creator...
//        if the program compiles and runs but a window doesn't open up
//        try un-checking "run in terminal"


// Here are some of the basic drawing commands:

//void   line(Vec2d p1, Vec2d p2, Color c = WHITE);
//void   ellipse(Vec2d center, double w, double h, Color c = WHITE, Color f = TRANSPARENT);
//void   arc(Vec2d center, double w, double h, double a, double alen, Color c = WHITE);
//void   chord(Vec2d center, double w, double h, double a, double alen, Color c = WHITE, Color f = TRANSPARENT);
//void   pie(Vec2d center, double w, double h, double a, double alen, Color c = WHITE, Color f = TRANSPARENT);
//void   rect(Vec2d corner, double w, double h, Color c = WHITE, Color f = TRANSPARENT);
//void   polygon(std::vector<Vec2d> pts, Color border, Color fill = TRANSPARENT);
//void   polyline(std::vector<Vec2d> pts, Color color);
//void   text(Vec2d pos, double size, const std::string& str, Color textColor = WHITE, HAlign hAlign = HAlign::left, VAlign vAlign = VAlign::baseline);

Color shiftColor(Color c)
{
    double h;
    double s;
    double v;
    rgb2hsv(c, h, s, v);
    h += 1;
    if (h > 360.0) {
        h -= 360;
    }
    return hsv2rgb(h, s, v);
}


bool pointInPolygon(Vec2d p, const vector<Vec2d>& pts){
    double slope = 0;
    int x = 0;
    int numInts = 0;
    if(pts.empty()){
        return false;
    }
    for(int i = 0; i < pts.size(); i++){
        if(p.x == pts[i].x && p.y == pts[i].y){
            return false;
        }
    }
    for(int i = 0; i < pts.size(); i++){
        Vec2d p1 = pts[i];
        Vec2d p2 = pts[(i+1)%pts.size()];
        if((p.y >= p1.y && p.y < p2.y) || (p.y < p1.y && p.y >= p2.y)){
            if((p1.x - p2.x) != 0){
                slope = (p1.y-p2.y)/(p1.x-p2.x);
                if(p1.y > p2.y){
                    x = (p.y-p2.y)/slope;
                    if(p2.x+x > p.x){
                        numInts++;
                    }
                }
                else if(p1.y < p2.y){
                    x = (p.y-p1.y)/slope;
                    if(p1.x+x > p.x){
                        numInts++;
                    }
                }
            }
            else{
                if(p1.x > p.x){
                    numInts++;
                }
            }
        }

    }
    if(numInts%2 == 1){
        return true;
    }
    else{
        return false;
    }
}


int main()
{
    Graphics g("Image Tweaker", 1024, 768);
    vector<Vec2d> polygon;
    while (g.draw()) {

        for(int i = 0; i < 10000; i++){
            double x = g.randomInt(0, g.width());
            double y = g.randomInt(0, g.height());
            if(pointInPolygon({x,y}, polygon)){
                g.ellipse({x,y}, 1, 1, GREEN, GREEN);
            }
            else{
                g.ellipse({x,y}, 1, 1, RED, RED);
            }
        }





        g.polygon(polygon, WHITE);

        if (g.isKeyPressed(Key::ESC)) {
            break;
        }
        if (g.isKeyPressed('R')) {
            polygon = {};
        }

        for (const Event& e : g.events()) {
            // g.cerr << e << endl;

            switch (e.evtType) {
            case EvtType::KeyPress:
                break;
            case EvtType::KeyRelease:
                break;
            case EvtType::MouseMove:
                break;
            case EvtType::MousePress:
                polygon.push_back(e.mousePos());
                break;
            case EvtType::MouseRelease:
                break;
            default:
                break;
            }
        }
    }

    return 0;
}


