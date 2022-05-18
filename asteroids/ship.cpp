#include "ship.h"
#include "graphics.h"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"
using namespace std;
using namespace mssm;

Sprites::Sprites(Vec2d location, double angle)
    :location{location}, angle{angle}
{

}

Ship::Ship(Vec2d location, double angle) : Sprites(location, angle)
{
    points = {
        {-20,-20},
        {0,-10},
        {20,-20},
        {0,30}
    };
}

vector<Vec2d> Ship::transform(Vec2d offset)
{
    vector<Vec2d> newPoints = points;
    for (int i = 0; i < newPoints.size(); i++) {
        newPoints[i].rotate(angle - M_PI/2);
        newPoints[i] = newPoints[i] * scale;
        newPoints[i] = newPoints[i] + location + offset;  // translation
    }
    return newPoints;
}

void Ship::draw(mssm::Graphics &g, Vec2d offset)
{
    g.polygon(transform(offset), color, color);
}

void Ship::physics(Graphics &g)
{
    location = location + velocity;
    velocity = velocity + acceleration;

    angle = angle + angleVelocity;

    if(location.x < -50)
    {
        location.x = g.width();
    }
    else if(location.x > g.width())
    {
        location.x = -50;
    }
    if(location.y < -50)
    {
        location.y = g.height();
    }
    else if(location.y > g.height())
    {
        location.y = -50;
    }
}

Bullet::Bullet(Vec2d location, double angle) : Sprites(location, angle)
{
    //bulletLocation = location;
}

void Bullet::drawBullets(Graphics &g)
{
    time++;
//    g.point(bulletLocation, YELLOW);
//    g.ellipseC(bulletLocation, 2, 2, YELLOW, YELLOW);
    g.point(location, YELLOW);
    g.ellipse(location, 2, 2, YELLOW, YELLOW);
}

void Bullet::updateBullets(Graphics& g)
{
    location += {10*cos(angle), 10*sin(angle)};
    if(location.x < -1)
    {
        location.x = g.width();
    }
    else if(location.x > g.width())
    {
        location.x = -1;
    }
    if(location.y < -1)
    {
        location.y = g.height();
    }
    else if(location.y > g.height())
    {
        location.y = -1;
    }
}
