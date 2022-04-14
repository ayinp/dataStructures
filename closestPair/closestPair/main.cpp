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
    void calculateDistance();
};

PointPair::PointPair(Vec2d p1, Vec2d p2)
    :p1{p1}, p2{p2}
{
    calculateDistance();
}

void PointPair::calculateDistance()
{
    double x = (p1.x - p2.x);
    double y = (p1.y - p2.y);
    distance = sqrt (pow(x,2) + pow(y,2));
}

PointPair closestPairBad(const vector<Vec2d>& points, Graphics& g){
    PointPair shortest({0,0}, {g.width(),g.height()});
    Vec2d p1;
    Vec2d p2;
    for(int i = 0; i < points.size(); i++){
        for(int j = 0; j < points.size(); j++){
            p1 = points[i];
            p2 = points[j];
            if(PointPair(p1, p2).distance < shortest.distance && j != i){
                shortest.p1 = p1;
                shortest.p2 = p2;
                shortest.calculateDistance();
            }
        }
    }
    return shortest;
}

PointPair recurseClosestPair(vector<Vec2d>& points){
    if(points.size() == 3){
        PointPair one(points[0], points[1]);
        PointPair two(points[1], points[2]);
        PointPair three(points[2], points[0]);
        if(one.distance <= two.distance && one.distance < three.distance){
            return one;
        }
        if(two.distance < one.distance && two.distance < three.distance){
            return two;
        }
        return three;
        //this is going to encounter issues if the distances are equal but i dont feel like fixing that rn
    }
    if(points.size() == 2){
        return PointPair(points[0], points[1]);
    }
    vector<Vec2d> pM;
    vector<Vec2d> pL;
    for(int i = 0; i < points.size(); i ++){
        if(i < points.size()/2){
            pL.push_back(points[i]);
        }
        else{
            pM.push_back(points[i]);
        }
    }
    PointPair lShort = recurseClosestPair(pL);
    PointPair rShort = recurseClosestPair(pM);

    if(rShort.distance < lShort.distance){
        return rShort;
    }
    return lShort;
}

PointPair closestPair(vector<Vec2d> points){
    sort(points.begin(), points.end(), [](Vec2d a, Vec2d b){return a.x < b.x;});
    return recurseClosestPair(points);
}


int main()
{
    Graphics g("MyProgram", 1024, 768);
    int numDotsX = 50;
    int numDotsY = numDotsX*g.height()/g.width();
    double nS = g.width()/numDotsX;
    double offset = nS/2;
    double cOX = (g.width()-(numDotsX * nS))/2;
    double cOY = (g.height()-(numDotsY * nS))/2;
    vector<Vec2d> points;

    for(int i = 0; i < numDotsX; i++){
        for (int j = 0; j < numDotsY; j++){
            Vec2d point = {(nS*i + g.randomDouble(0, offset) + cOX),(nS*j + g.randomDouble(0, offset) + cOY)};
            points.push_back(point);
        }
    }


    //    for(int i = 0; i < 1000; i++){
    //        Vec2d point = {g.randomDouble(0, g.width()),g.randomDouble(0, g.height())};
    //        points.push_back(point);
    //    }


    while (g.draw()) {

        g.points(points, WHITE);

        Vec2d p1 = closestPairBad(points, g).p1;
        Vec2d p2 = closestPairBad(points, g).p2;
        Vec2d p3 = closestPair(points).p1;
        Vec2d p4 = closestPair(points).p2;

        g.ellipse(p1, 10, 10, RED, RED);
        g.ellipse(p2, 10, 10, RED, RED);
        g.ellipse(p3, 3, 3, GREEN, GREEN);
        g.ellipse(p4, 3, 3, GREEN, GREEN);

        if (g.isKeyPressed(Key::ESC)) {
            break;
        }

        //make button to regenerate random points

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
