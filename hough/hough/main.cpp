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
vector<Vec2d/*vector<int>*/> Hough(const vector<Vec2d>& points, double maxR, int numR, int numTheta){
    vector<Vec2d> rTheta;
    double r = 0;
    for(int i = 0; i < points.size(); i++){
        for(int theta = 0; theta < 2*M_PI; theta += 2*M_PI/numTheta){
            r = points[i].x*cos(theta) + points[i].y*sin(theta);
            rTheta.push_back({r, theta});
        }
    }
    return rTheta;
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
        cout << line << endl;
        cout << "{" << x << ", " << y << "}" << endl;
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

    vector<Vec2d> hough = Hough(points, 0, 0, 20);

    while (g.draw()) {

        g.points(points, RED);
        g.points(hough, GREEN);


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


