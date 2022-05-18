#include <iostream>
#include "graphics.h"
#include <iomanip>

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


double calculateAngle(Vec2d a, Vec2d b, Vec2d c){

    Vec2d ab = a - b;
    Vec2d cb = c - b;

    double dot = ab.x * cb.x + ab.y * cb.y;

    double abM = ab.magnitude();
    double cbM = cb.magnitude();

    double cos = dot / (abM * cbM);

    double angle = acos(cos);



    return angle/(M_PI/180);
}

vector<Vec2d> giftWrapping(vector<Vec2d> points){

    vector<Vec2d> hull;
    int index = 0;
    int origionalIndex = 0;

    //find top point
    Vec2d topPoint = points[0];
    for(int i = 0; i < points.size(); i++){
        if(points[i].y < topPoint.y){
            topPoint = points[i];
            index = i;
            origionalIndex = i;
        }
    }
    hull.push_back(topPoint);

    Vec2d prev = {topPoint.x + 100, topPoint.y};
    Vec2d curr = topPoint;
    double smallestAngle = 0;
    int smallestIndex = origionalIndex + 1;


    //find smallest angle;

    while(smallestIndex != origionalIndex){
        //        cout << smallestIndex << endl;
        //        cout << origionalIndex << endl;
        smallestAngle = 0;
        for(int i = 0; i < points.size(); i++){
            if(i != index){
                double a = calculateAngle(prev, curr, points[i]);
                if(a > smallestAngle){
                    cout << a << " < " << smallestAngle << endl;
                    smallestAngle = a;
                    smallestIndex = i;

                }
            }
        }
        prev = curr;
        curr = points[smallestIndex];
        index = smallestIndex;
        hull.push_back(curr);
        cout << smallestIndex << endl;
        if(hull.size() > points.size()){
            cout << "OH NO!!!" << endl;
            break;
        }
    }


    //return hull
    return hull;
}


int main()
{
    Graphics g("My Program", 1024, 768);

    vector<Vec2d> points;
    for(int i = 0; i < 10; i++){
        points.push_back({g.randomDouble(0, g.width()), g.randomDouble(0, g.height())});
    }

    vector<Vec2d> hull = giftWrapping(points);


    points.push_back(g.mousePos());

    while (g.draw()) {


        points.back() = g.mousePos();

        hull = giftWrapping(points);

                g.points(points, WHITE);

                g.polygon(hull, WHITE);
                for(int i = 0; i < hull.size(); i++){
                    g.ellipse(hull[i], 5, 5, RED, RED);
                    //g.text(hull[i]+Vec2d{10,10}, 20, to_string(i), WHITE);
                    if (i > 0 && i < (hull.size()-1)) {
                        g.text(hull[i]+Vec2d{10,10}, 20, to_string(calculateAngle(hull[i-1], hull[i], hull[i+1])));
                    }
                }


        if (g.isKeyPressed(Key::ESC)) {
            break;
        }

        for (const Event& e : g.events()) {
            switch (e.evtType) {
            case EvtType::KeyPress:
            {
                points.clear();
                for(int i = 0; i < 10; i++){
                    points.push_back({g.randomDouble(0, g.width()), g.randomDouble(0, g.height())});
                }

                hull = giftWrapping(points);
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


