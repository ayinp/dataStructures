

#ifndef ATMOSPHERE_H
#define ATMOSPHERE_H

#include "graphics.h"

class Atmosphere
{
public:
    Vec2d location;
    Vec2d velocity;
    int transparency;
public:
    virtual void draw(mssm::Graphics& g);
    virtual void update(mssm::Graphics &g);
};

class Bubbles : public Atmosphere
{
public:
    double diameter;
    bool isFilled;
public:
    Bubbles(mssm::Graphics &g);
    virtual void draw(mssm::Graphics& g) override;
    virtual void update(mssm::Graphics &g) override;
};


class Astroid : public Atmosphere
{
public:
    std::vector<Vec2d> points;
    int scale;
    double angle;
    int x;
    double angleVelocity;
public:
    Astroid(mssm::Graphics &g, int x);
    std::vector<Vec2d> transform();
    virtual void draw(mssm::Graphics& g) override;
    virtual void update(mssm::Graphics &g) override;
    double calcRad();
};


#endif // ATMOSPHERE_H
