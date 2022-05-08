#include <iostream>
#include "graphics.h"
#include <iomanip>
#include <fstream>
#include "paths.h"

using namespace std;
using namespace mssm;

#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif

// hough
// given:   set of vec2d points
//          maximum R
//          number of R
//          number of R "bins"
//          number of theta "bins"
//
// return: 2d array of "votes"


//pi/180 rad = degree
vector<vector<int>> Hough(const vector<Vec2d>& points, double maxR, int numR, int numTheta){
    vector<vector<int>> counts(numR, vector<int>(numTheta));

    double r = 0;
    for(int i = 0; i < points.size(); i++){
        for(double theta = 0; theta < 2*M_PI; theta += 2*M_PI/numTheta){
            r = points[i].x*cos(theta) + points[i].y*sin(theta);
            if(r >= 0){
            counts[r/(maxR/numR)][theta/((2*M_PI)/numTheta)]++;
            }
        }
    }
    return counts;
}


int main()
{
    Graphics g("MyProgram", 1920, 1080);

    vector<Vec2d> points;

    ifstream pointsFile(R"(C:\Users\annaj\Desktop\dataStructures\hough\hough\assets\Pts.csv)");

    string line;
    double x = 0;
    double y = 0;
    double lowestX = 0;
    double lowestY = 0;
    double bigestX = 0;
    double bigestY = 0;

    while (getline(pointsFile, line)){
        stringstream ss(line);
        ss >> x;
        ss.ignore(1); // ignore the comma
        ss >> y;

//    for (double x = 0; x < 1000; x++) {
//        double y = x*0.7;


//        cout << line << endl;
//        cout << "{" << x  << ", " << y << "}" << endl;
        points.push_back({x, y});
        if(x > bigestX){
            bigestX = x;
        }
        if(x < lowestX){
            lowestX = x;
        }
        if(y > bigestY){
            bigestY = y;
        }
        if(y < lowestY){
            lowestY = y;
        }
    }



    double xRange = bigestX - lowestX;
    double yRange = bigestY - lowestY;
    double scaleX = g.width()/xRange;
    double scaleY = g.height()/yRange;
    double scale = min(scaleX, scaleY);

    for(int i = 0; i < points.size(); i++){
        points[i].x += abs(lowestX);
        points[i].y += abs(lowestY);
        points[i] = scale*points[i];
    }


    int numTheta = 100;
    int numR = 100;
    double diag = sqrt((g.width()*g.width()) + (g.height()*g.height()));
    double highestR = diag;

    vector<vector<int>> houghInt = Hough(points, highestR, numR, numTheta);
    vector<Vec2d> hough;

    double highest = 0;
    int inI = 0;
    int inJ = 0;
    for(int i = 0; i < houghInt.size(); i++){
        for(int j = 0; j < houghInt[i].size(); j++){
            if(houghInt[i][j] > highest){
                inI = i;
                inJ = j;
                highest = houghInt[i][j];
            }
        }
    }

    double rad = inI * (highestR/numR);
    double theta = inJ * ((2*M_PI)/numTheta);

    Vec2d p = {rad, 0};
    p.rotate(theta);

    Vec2d q = p.rotated(M_PI/2);

    Vec2d p1 = p + q;
    Vec2d p2 = p - q;


    while (g.draw()) {

        g.points(points, RED);
//        g.points(hough, GREEN);

        g.line(p1, p2, YELLOW);

        for(int i = 0; i < houghInt.size(); i++){
            for(int j = 0; j < houghInt[i].size(); j++){
    //            if(houghInt[i][j] > 0){
    //                hough.push_back({j * 10, i * 10});
    //            }
                g.ellipse({j * 10, i * 10}, 0.02*houghInt[i][j], 0.02*houghInt[i][j], GREEN);
            }
        }


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


