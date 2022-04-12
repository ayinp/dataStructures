#include <iostream>
#include "graphics.h"
#include <iomanip>
#include <stdio.h>
#include <math.h>

using namespace std;
using namespace mssm;

#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif

class PointPair{
public:
    Vec2d p1;
    Vec2d p2;
    double distance;
public:
    PointPair(Vec2d p1, Vec2d p2);
    double calculateDistance();
};

PointPair::PointPair(Vec2d p1, Vec2d p2)
    :p1{p1}, p2{p2}
{
    calculateDistance();
}

double PointPair::calculateDistance()
{
    double x = (p1.x - p2.x);
    double y = (p1.y - p2.y);
    distance = sqrt (pow(x,2) + pow(y,2));
}

PointPair closestPair(const vector<Vec2d>& points, Graphics& g){
    PointPair shortest({0,0}, {g.width(),g.height()});
    Vec2d p1;
    Vec2d p2;
    for(int i = 0; i < points.size(); i++){
        for(int j = 0; j < points.size(); j++){
            p1 = points[i];
            p2 = points[j];
            if(PointPair(p1, p2).distance < shortest.distance){
                shortest.p1 = p1;
                shortest.p2 = p2;
                shortest.calculateDistance();
            }
        }
    }
    return shortest;
}

int main()
{
    Graphics g("MyProgram", 1024, 768);

    vector<Vec2d> points;
    for(int i = 0; i < 1000; i++){
        Vec2d point = {g.randomDouble(0, g.width()),g.randomDouble(0, g.height())};
        points.push_back(point);
    }


    while (g.draw()) {

        g.points(points, WHITE);

        Vec2d p1 = closestPair(points, g).p1;
        Vec2d p2 = closestPair(points, g).p2;

        g.ellipse(p1, 2, 2, RED, RED);
        g.ellipse(p2, 2, 2, RED, RED);

        if (g.isKeyPressed(Key::ESC)) {
            break;
        }

        for (const Event& e : g.events()) {
            switch (e.evtType) {
            case EvtType::KeyPress:
                break;
            case EvtType::KeyRelease:
                break;
            case EvtType::MouseMove:
                break;
            case EvtType::MousePress:
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
