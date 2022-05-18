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

    Vec2d ab = {b.x-a.x, b.y-a.y};
    Vec2d cb = {b.x-c.x, b.y-c.y};
    double dot = ab.x * cb.x + ab.y * cb.y;
    double abSqr = ab.x * ab.x + ab.y * ab.y;
    double cbSqr = cb.x * cb.x + cb.y * cb.y;
    double cosSqr = dot * dot / abSqr / cbSqr;
    double cos2 = 2 * cosSqr - 1;
    double alpha2 =
            (cos2 <= -1) ? M_PI :
                           (cos2 >= 1) ? 0 :
                                         acosf(cos2);

    double rslt = alpha2 / 2;

    double rs = rslt * 180. / M_PI;

    if (dot < 0){
        rs = 180 - rs;
    }
    double det = (ab.x * cb.y - ab.y * cb.y);
    if (det < 0){
        rs = -rs;
    }

    return rs*(M_PI/180);
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

    Vec2d p1 = {topPoint.x + 100, topPoint.y};
    Vec2d p2 = topPoint;
    double smallestAngle = 2*M_PI;
    int smallestIndex = origionalIndex + 1;


    //find smallest angle;

    while(smallestIndex != origionalIndex){
//        cout << smallestIndex << endl;
//        cout << origionalIndex << endl;
        smallestAngle = 2*M_PI;
        for(int i = 0; i < points.size(); i++){
            if(i != index){
                double a = calculateAngle(p1, p2, points[i]);
                if(a < smallestAngle){
                    cout << a << " < " << smallestAngle << endl;
                    smallestAngle = a;
                    smallestIndex = i;

                }
            }
        }
        index = smallestIndex;
        hull.push_back(points[smallestIndex]);
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

    while (g.draw()) {

        g.points(points, WHITE);

        for(int i = 0; i < hull.size(); i++){
            g.ellipse(hull[i], 5, 5, RED, RED);
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


