#ifndef SHIP_H
#define SHIP_H
#include "graphics.h"

class Sprites
{
public:
    Vec2d location;
    double angle;
public:
    Sprites(Vec2d location, double angle);
};

class Ship : public Sprites
{
public:
    Vec2d velocity = {0, 0};
    Vec2d acceleration = {0, 0};
    double angleVelocity = 0;
    double scale = 1;
    mssm::Color color = mssm::BLUE;
    std::vector<Vec2d> points;
public:
    Ship(Vec2d location, double angle);
    std::vector<Vec2d> transform(Vec2d offset);
    void draw(mssm::Graphics& g, Vec2d offset);
    void physics(mssm::Graphics& g);
};

class Bullet : public Sprites
{
public:
    int time = 0;
public:
    Bullet(Vec2d location, double angle);
    void drawBullets(mssm::Graphics& g);
    void updateBullets(mssm::Graphics& g);
};

#endif // SHIP_H
