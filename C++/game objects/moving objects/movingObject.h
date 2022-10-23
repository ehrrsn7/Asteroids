//
//  movingObject.h
//  Asteroids
//
//  Created by Elijah Harrison on 11/7/20.
//

#ifndef movingObject_hpp
#define movingObject_hpp

#include <iostream>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

#include "../../vector/vector.h"

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
    Position p;
    Velocity v;
    double r; // radius
    double da; // angular velocity
    double rotation; // orientation angle (in radians)
    double dr; // orientation angle angular vel.
    double thrust;
    double mass;
    double timer;
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
    Position getPosition()  const { return p; }
    Velocity getVelocity()  const { return v; }
    double getRadius()       const { return r; }
    double getRotation()     const { return rotation; }
    bool isAlive()          const { return alive; }
    double getMass()         const { return mass; }
    double getMomentum()     const { return mass * v.getMagnitude(); }
    int getScoreAmount()    const { return scoreAmount; }
    
    // setters
    void setPosition(Position new_p) { p = new_p; }
    void setPositionX(double new_x)   { p.setX(new_x); }
    void setPositionY(double new_y)   { p.setY(new_y); }
    void setVelocity(Velocity new_v) { v = new_v; }
    void setRadius(double new_r)      { r = new_r; }
    void setRotation(double new_dr)   { dr = new_dr; }
    void setAlive(bool new_alive)    { alive = new_alive; }
    void setDeathTimer(double duration);
};

#endif /* movingObject_hpp */
