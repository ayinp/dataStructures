#include <iostream>
#include <memory>
#include "graphics.h"
#include <cmath>
#include <fstream>
#include "atmosphere.h"
#include "ship.h"
#include "button.h"

#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"

using namespace std;
using namespace mssm;

//  is in space?
bool inPos(Vec2d point, Vec2d position, int radius1, int radius2)
{
   bool hit = (position - point).magnitude() <= radius1 + radius2;

   if (hit) {
       cout << "Boop" << endl;
   }
   return hit;
}

// loose lives
void lifeLost(Graphics& g, int lives)
{

    Vec2d rectPos;
    double width;
    double height;
    int textSize = 50;
    Vec2d location;    TextExtents te;
    g.textExtents(textSize, "Life Lost, you now have " + to_string(lives) + " left", te);
    width = te.textWidth;
    height = te.textHeight;
    location = {(g.width()-width)/2, (g.height()-height)/2};
    g.text(location, textSize, "Life Lost, you now have " + to_string(lives) + " left", RED);
}

// welcome
void welcome(Graphics& g, vector<Bubbles> higherBubbles, vector<Bubbles> lowerBubbles)
{
    Button play(g, "play", 100);
    Button title(g, "Asteroids :)", 150);
    while(g.draw())
    {
        g.clear();
        for(int i = 0; i < lowerBubbles.size(); i++)
        {
            lowerBubbles[i].draw(g);
            lowerBubbles[i].update(g);
        }
        play.location = {(g.width()-play.width)/2, (g.height()-play.height)/2 - 100};
        play.draw(g);
        title.location = {(g.width()-title.width)/2, (g.height()-title.height) - 50};
        title.draw(g);
        title.setColor(BLACK, WHITE, BLACK);
        play.color = BLUE;
        Vec2d mousePos = g.mousePos();
        if(play.inButton(mousePos))
        {
            play.outerColor = WHITE;
            play.textColor = WHITE;
        }
        else
        {
            play.outerColor = BLACK;
            play.textColor = BLACK;
        }
        for (const Event& e : g.events())
        {
            switch (e.evtType)
            {
            case EvtType::MousePress:
                if(play.inButton(mousePos))
                {
                    return;
                }
                break;
            case EvtType::MouseRelease:
                break;
            case EvtType::MouseWheel:
                break;
            case EvtType::MouseMove:
                break;
            case EvtType::KeyPress:
                break;
            case EvtType::KeyRelease:
                break;
            default:
                break;
            }
        }
        // higher bubbles
        for(int i = 0; i < higherBubbles.size(); i++)
        {
            higherBubbles[i].draw(g);
            higherBubbles[i].update(g);
        }

    }
}

//end
void end(Graphics& g, vector<Bubbles> higherBubbles, vector<Bubbles> lowerBubbles, int round, int score)
{
    Button playAgain(g,"play again?", 100);
    Button title(g,"You Lost! game over :(", 75);
    Button howMany(g,"you got to round " + to_string(round), 75);
    Button scoreNum(g,"with a score of " + to_string(score), 75);
    while(g.draw())
    {
        g.clear();
        for(int i = 0; i < lowerBubbles.size(); i++)
        {
            lowerBubbles[i].draw(g);
            lowerBubbles[i].update(g);
        }
        playAgain.location = {(g.width()-playAgain.width)/2, (g.height()-playAgain.height)/2 - 100};
        playAgain.draw(g);
        title.location = {(g.width()-title.width)/2, (g.height()-title.height) - 50};
        title.draw(g);
        howMany.location = {(g.width()-howMany.width)/2, (g.height()-howMany.height) - 60 - title.height};
        howMany.draw(g);
        scoreNum.location = {(g.width()-howMany.width)/2, (g.height()-howMany.height) - 60 - title.height - howMany.height};
        scoreNum.draw(g);
        title.setColor(BLACK, WHITE, BLACK);
        playAgain.color = BLUE;
        howMany.setColor(BLACK, WHITE, BLACK);
        scoreNum.setColor(BLACK, WHITE, BLACK);
        Vec2d mousePos = g.mousePos();
        if(playAgain.inButton(mousePos))
        {
            playAgain.outerColor = WHITE;
            playAgain.textColor = WHITE;
        }
        else
        {
            playAgain.outerColor = BLACK;
            playAgain.textColor = BLACK;
        }
        for (const Event& e : g.events())
        {
            switch (e.evtType)
            {
            case EvtType::MousePress:
                if(playAgain.inButton(mousePos))
                {
                    return;
                }
                break;
            case EvtType::MouseRelease:
                break;
            case EvtType::MouseWheel:
                break;
            case EvtType::MouseMove:
                break;
            case EvtType::KeyPress:
                break;
            case EvtType::KeyRelease:
                break;
            default:
                break;
            }
        }
        // higher bubbles
        for(int i = 0; i < higherBubbles.size(); i++)
        {
            higherBubbles[i].draw(g);
            higherBubbles[i].update(g);
        }

    }
}

// main
void graphicsMain(Graphics& g)
{
    //bubbles
    vector<Bubbles> lowerBubbles;
    vector<Bubbles> higherBubbles;
    int numLowerBubbles = 350;
    int numHigherBubbles = 150;
    for(int i = 0; i < numLowerBubbles; i++)
    {
        lowerBubbles.push_back(Bubbles(g));
    }
    for(int i = 0; i < numHigherBubbles; i++)
    {
        higherBubbles.push_back(Bubbles(g));
    }
    welcome(g, higherBubbles, lowerBubbles);

    // ship tings
    Ship ship{{g.width()/2, g.height()/2}, 0};


    // bullets
    vector<Bullet> bullets;
    int time = 0;

    // astroids
    int round = 1;
    vector<Astroid> astroids;
    int numAstroids = 4;
    for(int i = 0; i < numAstroids+round; i++)
    {
        astroids.push_back(Astroid(g, g.randomInt(0, 2)));
    }
    vector<Astroid> backUpAstroids = astroids;

    //rounds
    int lives = 3;
    bool colide = false;
    int showTime = 0;
    int score = 0;

    // draw
    while (g.draw()) {
        g.clear();


        // lower bubbles
        for(int i = 0; i < lowerBubbles.size(); i++)
        {
            lowerBubbles[i].draw(g);
            lowerBubbles[i].update(g);
        }

        // ship
        ship.draw(g, {0,0});
        ship.physics(g);

        // rotate
        if(showTime <= 0 && (g.isKeyPressed('A') || g.isKeyPressed(Key::Left)))
        {
            ship.angleVelocity = 0.1;
        }
        else if(showTime <= 0 && (g.isKeyPressed('D') || g.isKeyPressed(Key::Right)))
        {
            ship.angleVelocity = -0.1;
        }
        else
        {
            ship.angleVelocity *= 0.85;
            if(ship.angleVelocity == 0)
            {
                ship.angleVelocity = 0;
            }
        }

        // move
        if(showTime <= 0 && (g.isKeyPressed('W') || g.isKeyPressed(Key::Up)))
        {
            ship.acceleration = {0.5*cos(ship.angle), 0.5*sin(ship.angle)};
        }
        else if(showTime <= 0 && (g.isKeyPressed('S') || g.isKeyPressed(Key::Down)))
        {
            ship.acceleration = {0, 0};
            ship.velocity = ship.velocity * 0.95;
            if(ship.velocity.magnitude() < 0.0001)
            {
                ship.velocity = {0, 0};
            }
        }
        else
        {
            ship.acceleration = {0, 0};
        }

        // shoot
        if(showTime <= 0 && g.isKeyPressed(' '))
        {
            if(time%10 == 0)
            {
                bullets.push_back(Bullet{ship.location, ship.angle});
            }
            time++;
        }
        else
        {
            time = 0;
        }

        // draw bullets
        for(int i = 0; i < bullets.size(); i++)
        {
            bullets[i].drawBullets(g);
            bullets[i].updateBullets(g);
            bullets[i].time++;
            if(bullets[i].time > 200)
            {
                bullets.erase(bullets.begin()+ i);
            }
        }

        // draw asteroids
        for(int i = 0; i < astroids.size(); i++)
        {
            astroids[i].draw(g);
            astroids[i].update(g);
        }

        // clicks an things
        for (const Event& e : g.events())
        {
            switch (e.evtType)
            {
            case EvtType::MousePress:
                break;
            case EvtType::MouseRelease:
                break;
            case EvtType::MouseWheel:
                break;
            case EvtType::MouseMove:
                break;
            case EvtType::KeyPress:
                break;
            case EvtType::KeyRelease:
                break;
            default:
                break;
            }
        }


        // higher bubbles
        for(int i = 0; i < higherBubbles.size(); i++)
        {
            higherBubbles[i].draw(g);
            higherBubbles[i].update(g);
        }


        // astroid go boom?
        for(int i = 0; i < bullets.size(); i++)
        {
            for(int j = 0; j < astroids.size(); j++)
            {
                if(inPos(bullets[i].location, astroids[j].location, astroids[j].calcRad(), 1))
                {
                    // g.text({25, g.height() - 25}, 25, "boom", WHITE);
                    bullets.erase(bullets.begin() + i);
                    i--;
                    if(astroids[j].x == 2)
                    {
                        Astroid a1(g, 1);
                        a1.location = astroids[j].location;
                        Astroid a2(g, 1);
                        a2.location = astroids[j].location;
                        astroids.push_back(a1);
                        astroids.push_back(a2);
                        astroids.erase(astroids.begin() + j);
                        j--;
                        score = score + 2;
                        break;
                    }
                    else if(astroids[j].x == 1)
                    {
                        Astroid a1(g, 0);
                        a1.location = astroids[j].location;
                        Astroid a2(g, 0);
                        a2.location = astroids[j].location;
                        astroids.push_back(a1);
                        astroids.push_back(a2);
                        astroids.erase(astroids.begin() + j);
                        j--;
                        score = score + 5;
                        break;
                    }
                    else if(astroids[j].x == 0)
                    {
                        astroids.erase(astroids.begin() + j);
                        j--;
                        score = score + 10;
                        break;
                    }
                }
            }
        }

        // words lol
        g.text({20, g.height()-25}, 25, "Round: " + to_string(round), WHITE);
        g.text({20, g.height()-50}, 25, "Lives: " + to_string(lives), WHITE);
        g.text({20, g.height()-75}, 25, "Asteroids: " + to_string(astroids.size()), WHITE);
        g.text({20, g.height()-100}, 25, "Score: " + to_string(score), WHITE);

        // new round
        if(astroids.size() == 0)
        {
            round++;
            for(int i = 0; i < numAstroids+round-1; i++)
            {
                astroids.push_back(Astroid(g, g.randomInt(0, 2)));
            }
            backUpAstroids = astroids;
        }

        // check for ship/astroid collision
        for (int i = 0; i < astroids.size(); i++)
        {
            if(inPos(ship.location, astroids[i].location, astroids[i].calcRad(), 20))
            {
                lives--;
                ship.location = {g.width()/2, g.height()/2};
                ship.velocity = {0,0};
                ship.angle = 0;
                astroids = backUpAstroids;
                colide = true;
            }
        }

        // make collision actually display things bc im cool lol
        if(colide)
        {
            showTime++;
            if(showTime <= 50)
            {
                lifeLost(g, lives);
            }
            else if(showTime > 50)
            {
                colide = false;
                showTime = 0;
            }
        }


        // make ship flash
        if (showTime%10 > 5)
        {
            ship.color = WHITE;
        }
        else
        {
            ship.color = BLUE;
        }


        // loose condition
        if(lives <= 0)
        {
            end(g, higherBubbles, lowerBubbles, round, score);
            round = 1;
            lives = 3;
            showTime = 0;
            score = 0;
            astroids.clear();
            bullets.clear();
            ship.location = {g.width()/2, g.height()/2};
            ship.velocity = {0,0};
            ship.angle = 0;
            for(int i = 0; i < numAstroids+round; i++)
            {
                astroids.push_back(Astroid(g, g.randomInt(0, 2)));
            }
            backUpAstroids = astroids;
            colide = false;
        }

    }
}


int main(int /*argc*/, char** /*argv*/)
{
    // main should be empty except for the following line:
    Graphics g("Graphics", 1200, 800, graphicsMain);
    return 0;
}



