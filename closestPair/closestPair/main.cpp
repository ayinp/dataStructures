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

bool inLessThanEnd(int in, int size){
    return (size-in) > 0;
}

PointPair recurseClosestPair(vector<Vec2d>& points){
    if(points.size() == 3){
        PointPair one(points[0], points[1]);
        PointPair two(points[1], points[2]);
        PointPair three(points[2], points[0]);

        sort(points.begin(), points.end(), [](Vec2d a, Vec2d b){return a.y < b.y;});

        if(one.distance <= two.distance && one.distance < three.distance){
            return one;
        }
        if(two.distance < one.distance && two.distance < three.distance){
            return two;
        }
        return three;
    }
    if(points.size() == 2){

        if(points[0].y > points[1].y){
            swap(points[0], points[1]);
        }

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

    vector<Vec2d> newSort = {};
    int Lin = 0;
    int Rin = 0;
    while(inLessThanEnd(Rin, pM.size()) || inLessThanEnd(Lin, pL.size())){

        if((inLessThanEnd(Rin, pM.size()) && inLessThanEnd(Lin, pL.size())) && pL[Lin].y > pM[Rin].y){
            newSort.push_back(pM[Rin]);
            Rin++;
        }
        else if((inLessThanEnd(Rin, pM.size()) && inLessThanEnd(Lin, pL.size())) && (pL[Lin].y < pM[Rin].y || pL[Lin].y == pM[Rin].y)){
            newSort.push_back(pL[Lin]);
            Lin++;
        }
        else if(!inLessThanEnd(Rin, pM.size()) && inLessThanEnd(Lin, pL.size())){
            newSort.push_back(pL[Lin]);
            Lin++;
        }
        else if(inLessThanEnd(Rin, pM.size()) && !inLessThanEnd(Lin, pL.size())){
            newSort.push_back(pM[Rin]);
            Rin++;
        }
    }
    if (points.size() != newSort.size()) {
        cout << "BAAAAADdaDadadd" << endl;
    }

    points = newSort;


    for(int i = 1; i < points.size(); i++){
        if(!(points[i].y > points[i-1].y)){
            cout << "NOOOOOOOOOOOOOOOOOOOOOO" << endl;
        }
    }

    PointPair currentShortest({0,0}, {0,0});
    double splitPoint = (pM[0].x + pL[pL.size()-1].x)/2;
    double dMore;
    double dLess;
    if(rShort.distance < lShort.distance){
        dMore = splitPoint + rShort.distance;
        dLess = splitPoint - rShort.distance;
        currentShortest = rShort;
    }
    else{
        dMore = splitPoint + lShort.distance;
        dLess = splitPoint - lShort.distance;
        currentShortest = lShort;
    }
    vector<Vec2d> strip;
    for(int i = 0; i < points.size(); i++){
        if(points[i].x <= dMore && points[i].x >= dLess){
            strip.push_back(points[i]);
        }
    }
    if(strip.size() == 0){
        return currentShortest;
    }

    PointPair current({0,0}, {0,0});
    for(int i = 0; i < strip.size(); i++){
        for(int j = i+1; j < strip.size(); j++){
            current.p1 = strip[i];
            current.p2 = strip[j];
            current.calculateDistance();
            if(abs(current.p1.y - current.p2.y) > currentShortest.distance){
                break;
            }
            if(current.distance < currentShortest.distance){
                currentShortest = current;
            }
        }
    }




    return currentShortest;

}

PointPair closestPair(vector<Vec2d> points){
    sort(points.begin(), points.end(), [](Vec2d a, Vec2d b){return a.x < b.x;});
    return recurseClosestPair(points);
}


int main()
{
    Graphics g("MyProgram", 1024, 768);
    int numDotsX = 5;
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

    PointPair bad = closestPairBad(points,g);
    PointPair good = closestPair(points);

    bool gotBad = false;

    while (g.draw()) {

        g.points(points, WHITE);


        g.ellipse(bad.p1, 10, 10, RED, RED);
        g.ellipse(bad.p2, 10, 10, RED, RED);
        g.ellipse(good.p1, 3, 3, GREEN, GREEN);
        g.ellipse(good.p2, 3, 3, GREEN, GREEN);
        g.line(good.p1, good.p2, GREEN);

        g.text({25, 25}, 25, to_string(good.distance), GREEN);
        g.text({25, 50}, 25, to_string(bad.distance), RED);

        if (g.isKeyPressed(Key::ESC)) {
            break;
        }

        if(bad.distance < good.distance){
           // cout << "cry" << endl;
            gotBad = true;
        }

        //make button to regenerate random points

        for (const Event& e : g.events()) {
            switch (e.evtType) {
            case EvtType::KeyPress:
                if (e.arg == 'R' && !gotBad) {
                    points.clear();
                    for(int i = 0; i < numDotsX; i++){
                        for (int j = 0; j < numDotsY; j++){
                            Vec2d point = {(nS*i + g.randomDouble(0, offset) + cOX),(nS*j + g.randomDouble(0, offset) + cOY)};
                            points.push_back(point);
                        }
                    }
                    bad = closestPairBad(points,g);
                    good = closestPair(points);
                }
                if (e.arg == 'T') {
                    good = closestPair(points);
                }
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
