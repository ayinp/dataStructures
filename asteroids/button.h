#ifndef BUTTON_H
#define BUTTON_H
#include "graphics.h"


class Button
{
public:
    double width;
    double height;
    Vec2d location;
    std::string text;
    int textSize;
    mssm::Color color = mssm::WHITE;
    mssm::Color textColor = mssm::BLACK;
    mssm::Color outerColor = mssm::BLACK;

public:
    Button(mssm::Graphics &g, std::string text, int textSize, Vec2d location = {0,0});
    Button();
    bool inButton(Vec2d position);
    void draw(mssm::Graphics& g);
    void setColor(mssm::Color color, mssm::Color textColor, mssm::Color outerColor = mssm::BLACK);

};

#endif // BUTTON_H
