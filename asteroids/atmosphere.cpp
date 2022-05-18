#include "atmosphere.h"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"
using namespace mssm;
using namespace std;

void Atmosphere::draw(Graphics& /*g*/)
{

}

void Atmosphere::update(Graphics& /*g*/)
{

}



Bubbles::Bubbles(Graphics& g)
{
    location = {g.randomDouble(0, g.width()-diameter), g.randomDouble(0, g.height()-diameter)};
    velocity = {g.randomDouble(-1, 1), g.randomDouble(-1, 1)};
    transparency = rand()%200+25;
    diameter = g.randomDouble(0.2, 5);
    isFilled = rand()%2;
}

void Bubbles::draw(mssm::Graphics& g)
{
    if(isFilled == false)
    {
        g.ellipse(location, diameter, diameter, {128,128,128, transparency});
    }
    else if(isFilled == true)
    {
        g.ellipse(location, diameter, diameter, {128,128,128, transparency}, {128,128,128, transparency});
    }
}

void Bubbles::update(Graphics& g)
{
    location += velocity;
    if(location.x <= 0 - diameter)
    {
        location.x = g.width();
    }
    else if(location.x >= g.width())
    {
        location.x = 0 - diameter;
    }
    else if(location.y <= 0 - diameter)
    {
        location.y = g.height();
    }
    else if(location.y >= g.height())
    {
        location.y = 0 - diameter;
    }
}


Astroid::Astroid(Graphics& g, int x)
{
    this->x = x;
    switch(x)
    {
    case 2:
        scale = 8;
        break;
    case 1:
        scale = 4;
        break;
    case 0:
        scale = 2;
        break;
    }
    int aboveBelow = g.randomInt(0,1);
    int leftRight = g.randomInt(0,1);
    if(leftRight == 0)
    {
        location.x = g.randomDouble(0, g.width()/2 - 150);
    }
    else if(leftRight == 1)
    {
        location.x = g.randomDouble(g.width()/2 + 150, g.width()-calcRad()*2);
    }
    if(aboveBelow == 0)
    {
        location.y = g.randomDouble(0, g.width()/2 - 150);
    }
    else if(aboveBelow == 1)
    {
         location.y = g.randomDouble(g.width()/2 + 150, g.width()-calcRad()*2);
    }
    int posNegXVel = g.randomInt(0,1);
    int posNegYVel = g.randomInt(0,1);
    int low = 1;
    int high = 5;
    if(posNegXVel == 0)
    {
        velocity.x = g.randomDouble(low, high);
    }
    else if(posNegXVel == 1)
    {
        velocity.x = g.randomDouble(-1*high, -1*low);
    }
    if(posNegYVel == 0)
    {
        velocity.y = g.randomDouble(low, high);
    }
    else if(posNegYVel == 1)
    {
         velocity.y = g.randomDouble(-1*high, -1*low);
    }
    points = vector<Vec2d>{{0,-12}, {-8,-9}, {-12,-2}, {-10,6}, {-4,12}, {4,12}, {10,6}, {12,-2}, {8,-9}};
    transparency = rand()%155+100;
    angle = g.randomDouble(0, 3.14);
    angleVelocity =g.randomDouble(-0.1, 0.1);
}

vector<Vec2d> Astroid::transform()
{
    vector<Vec2d> newPoints = points;
    for (int i = 0; i < newPoints.size(); i++) {
        newPoints[i].rotate(angle - M_PI/2);
        newPoints[i] = newPoints[i] * scale;
        newPoints[i] = newPoints[i] + location;
    }
    return newPoints;
}

void Astroid::draw(Graphics& g)
{
    g.polygon(transform(), {128,128,128, transparency}, {128,128,128, transparency});
}

void Astroid::update(Graphics& g)
{
    location += velocity;
    angle = angle + angleVelocity;
    if(location.x <= 0 - calcRad()*2)
    {
        location.x = g.width();
    }
    else if(location.x >= g.width())
    {
        location.x = 0 - calcRad()*2;
    }
    else if(location.y <= 0 - calcRad()*2)
    {
        location.y = g.height();
    }
    else if(location.y >= g.height())
    {
        location.y = 0 - calcRad()*2;
    }
}

double Astroid::calcRad()
{
    return scale*12;
}


