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

int main()
{
    Graphics g("Image Tweaker", 1024, 768);

    Image blue(g, 100, 100, BLUE, true);  // << the "true" here sets this up to allow you to modify pixels
    Image skull(g, "skull.png", true);    //


    Color* pixels = blue.pixels();  // get a point to the pixel buffer

    for (int i = 0; i < 100; i++) {
        pixels[i+i*100] = YELLOW;   // change some pixels
    }

    blue.updatePixels();            // this updates the image with the changes you made

    while (g.draw()) {

        g.image({50,50}, blue);

        g.image({200,200}, skull);

        if (g.isKeyPressed(Key::ESC)) {
            break;
        }

        if (g.isKeyPressed(' ')) {
            // not the most efficient way to do this, but it is intuitive for new programmers
            for (int x = 0; x < skull.width(); x++) {
                for (int y = 0; y < skull.height(); y++) {
                    Color c = skull.getPixel(x, y);
                    skull.setPixel(x, y, shiftColor(c));
                }
            }

            skull.updatePixels();

            // more efficient
            {
                Color* pixels = blue.pixels();
                for (int i = blue.width() * blue.height(); i >= 0; i--) {
                    *pixels = shiftColor(*pixels);
                    pixels++;
                }
            }

            blue.updatePixels();
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


