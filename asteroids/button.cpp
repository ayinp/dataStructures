#include "button.h"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"
using namespace mssm;
using namespace std;

Button::Button()
{

}

Button::Button(Graphics& g, string label, int size, Vec2d location)
{
    this->location = location;
    text = label;
    textSize = size;
    location = {0, 0};

    TextExtents te;
    g.textExtents(textSize, label, te);
    width = te.textWidth;
    height = te.textHeight;
}

bool  Button::inButton(Vec2d position)
{
    return position.x >= location.x &&
           position.x <= location.x + width &&
           position.y >= location.y &&
           position.y <= location.y + height;
}

void Button::draw(Graphics& g)
{
    TextExtents te;
    g.textExtents(textSize, text, te);
    width = te.textWidth;
    height = te.textHeight;
    Vec2d rectPos = location;
    g.rect(rectPos-Vec2d{textSize/4, height + te.fontDescent}, width + textSize/2, height, outerColor, color);
    g.text(location, textSize, text, textColor);
    location = rectPos;

}

void Button::setColor(Color color, Color textColor, Color outerColor)
{
    this->color = color;
    this->textColor = textColor;
    this->outerColor = outerColor;
}
