//
//  movingObject.hpp
//  Asteroids
//
//  Created by Elijah Harrison on 11/7/20.
//

#ifndef movingObject_hpp
#define movingObject_hpp

#include <iostream>
#include <string>
#include <math.h>

#include "point.hpp"
#include "velocity.hpp"

#define FPS 60.0

enum gameObjectEnumID {
    movingObject,
    rock,
    laser,
    playerShip,
    ufo,
    score,
    level
};

class MovingObject {

protected:
    int gameObjectID;
    std::string name;
    Point p;
    Velocity v;
    float r; // radius
    float da; // angular velocity
    float rotation; // orientation angle (in radians)
    float dr; // orientation angle angular vel.
    float thrust;
    float mass;
    float timer;
    int scoreAmount;
    bool timerOn; // self-destruct timer y/n
    bool alive; // is alive y/n
    bool friction; // apply friction/slow down object naturally
    bool brake; // apply brakes/slow down object when brakes are activated
    
    // debug
    int i;

public:
    MovingObject() {
        gameObjectID = movingObject;
        name        = "* Moving object";
        r           = 10.0; // in pixels
        rotation    = 0.0; // current orientation angle (degrees)
        dr          = 0.0; // orientation angle rot. vel. in deg. per second
        thrust      = 0.0; // acceleration in pixels/s/s
        mass        = 1.0; // kg (default)
        timer       = 0.0; // self-destruct timer in seconds
        scoreAmount = 0; // points to be added to score when destroyed (if applicable)
        timerOn     = false; // self-destruct timer y/n
        alive       = true; // is alive y/n
        friction    = false; // apply friction/brakes
        brake       = false; // apply brakes
        
        // debug
        i           = 0;
        // std::cout << name << " constructor called." << std::endl;
    }

    void update() {
        // quick exit
        if (!alive) return;

        // displayDebugUpdateInfo(); // debug

        // update position
        p.add(v);

        // update orientation angle ('rotation')
        rotation += dr / FPS;
        if (rotation < 0) rotation = M_PI*2;
        else if (rotation > M_PI*2) rotation = 0;
        
        // update timer (if timer == 0, do nothing)
        if (timerOn) {
            if (timer > 0) timer -= 1.0;
            else alive = false;
        }
    }
    
    void displayDebugUpdateInfo();
    void accelerate();
    void hit();

    // polymorphism
    virtual void display() { }

    // getters
    std::string getName()   const { return name; }
    int getGameObjectID()   const { return gameObjectID; }
    Point getPoint()        const { return p; }
    Velocity getVelocity()  const { return v; }
    float getRadius()       const { return r; }
    float getRotation()     const { return rotation; }
    bool isAlive()          const { return alive; }
    float getMass()         const { return mass; }
    float getMomentum()     const { return mass * v.getSpeed(); }
    int getScoreAmount()    const { return scoreAmount; }
    
    // setters
    void setPoint(Point new_p)       { p = new_p; }
    void setPointX(float new_x)      { p.setX(new_x); }
    void setPointY(float new_y)      { p.setY(new_y); }
    void setVelocity(Velocity new_v) { v = new_v; }
    void setRadius(float new_r)      { r = new_r; }
    void setRotation(float new_dr)   { dr = new_dr; }
    void setAlive(bool new_alive)    { alive = new_alive; }
    void setDeathTimer(float duration);
};

#endif /* movingObject_hpp */
