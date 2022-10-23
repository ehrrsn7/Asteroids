//
//  rocks.hpp
//  Asteroids
//
//  Created by Elijah Harrison on 11/14/20.
//

#ifndef rocks_hpp
#define rocks_hpp

#include <iostream>

#include "movingObject.hpp"
#include "uiDraw.hpp"

#define ROCK_INIT_AMOUNT 3 // amount of rocks spawned in first level scene
#define ROCK_INIT_LAUNCH_FORCE 5 // force applied to rocks that are spawned in N

#define ROCK_RADIUS 10 // size of rock in px
#define BIG_ROCK_RADIUS 10
#define MEDIUM_ROCK_RADIUS 5
#define SMALL_ROCK_RADIUS 3

#define ROCK_ROTATE_SPEED 10 // rotational velocity of rocks in rad/s
#define BIG_ROCK_ROTATE_SPEED 10
#define MEDIUM_ROCK_ROTATE_SPEED 15
#define SMALL_ROCK_ROTATE_SPEED 20

#define ROCK_MASS 100 // mass of rocks in kg
#define BIG_ROCK_MASS 100
#define MEDIUM_ROCK_MASS 80
#define SMALL_ROCK_MASS 50

#define ROCK_SCORE 20
#define BIG_ROCK_SCORE 20
#define MEDIUM_ROCK_SCORE 50
#define SMALL_ROCK_SCORE 100


// rock ids
enum rockIndex {
    unknownRock,
    bigRock,
    mediumRock,
    smallRock,
    noRock
};


class Rock : public MovingObject {
protected:
    int rockIndex;

public:
    Rock() {
        name = "Rock (unknown)";
        gameObjectID = rock;
        rockIndex = unknownRock;
        r = ROCK_RADIUS;
        dr = ROCK_ROTATE_SPEED * random(-1.0, 1.0);
        initializePosition();
        initializeVelocity();
        scoreAmount = ROCK_SCORE;
        std::cout << "* " << name << " constructor called." << std::endl;
    }

    void display() override {
        // debug (pt. 1; pt. 2 located in drawLargeAsteroid())
        // std::cout << name << ".display() called. // ";
        
        // Draw asteroid at Point p and angle r
        drawLargeAsteroid(p, rotation);
    }

    void initializeRotation();
    void initializePosition();
    void initializePosition(Point pInit);
    void initializeVelocity();
    void initializeVelocity(Velocity vInit);
    
    const static int amountInit = ROCK_INIT_AMOUNT;
    
    // getters/setters
    int getRockIndex() { return rockIndex; }
    int getNextRockIndex() {
        switch(rockIndex) {
            case unknownRock:
            case bigRock:
            case mediumRock:
            case smallRock:
                return rockIndex + 1;
            default:
                return noRock;
        };
    }
    
    static int getRockRadius(int rockID) {
        switch (rockID) {
            case bigRock:    return BIG_ROCK_RADIUS;
            case mediumRock: return MEDIUM_ROCK_RADIUS;
            case smallRock:  return SMALL_ROCK_RADIUS;
            default:         return ROCK_RADIUS;
        }
    }
    
    static float getRockRotateSpeed(int rockID) {
        switch (rockID) {
            case bigRock:    return BIG_ROCK_ROTATE_SPEED;
            case mediumRock: return MEDIUM_ROCK_ROTATE_SPEED;
            case smallRock:  return SMALL_ROCK_ROTATE_SPEED;
            default:         return ROCK_ROTATE_SPEED;
        }
    }
};

class BigRock : public Rock {
public:
    BigRock(Point pInit, Velocity vInit) {
        name = "Big Rock";
        rockIndex = bigRock;
        r = BIG_ROCK_RADIUS;
        initializePosition(pInit);
        initializeVelocity(vInit);
        scoreAmount = BIG_ROCK_SCORE;
    }
};

class MediumRock : public Rock {
public:
    MediumRock(Point pInit, Velocity vInit) {
        name = "Medium Rock";
        rockIndex = mediumRock;
        r = MEDIUM_ROCK_RADIUS;
        initializePosition(pInit);
        initializeVelocity(vInit);
        scoreAmount = MEDIUM_ROCK_SCORE;
    }
    MediumRock(Point pInit, Velocity vInit, Velocity vShipInit) {
        name = "Medium Rock";
        rockIndex = mediumRock;
        r = MEDIUM_ROCK_RADIUS;
        initializePosition(pInit);
        initializeVelocity(vInit);
        scoreAmount = MEDIUM_ROCK_SCORE;
    }
    
    void display() override {
        drawMediumAsteroid(p, rotation);
    }
};

class SmallRock : public Rock {
public:
    SmallRock(Point pInit, Velocity vInit) {
        name = "Small Rock";
        rockIndex = smallRock;
        r = SMALL_ROCK_RADIUS;
        initializePosition(pInit);
        initializeVelocity(vInit);
        scoreAmount = SMALL_ROCK_SCORE;
    }
    SmallRock(Point pInit, Velocity vInit, Velocity vShipInit) {
        name = "Small Rock";
        rockIndex = smallRock;
        r = SMALL_ROCK_RADIUS;
        initializePosition(pInit);
        initializeVelocity(vInit);
        scoreAmount = SMALL_ROCK_SCORE;
    }
    
    void display() override {
        drawSmallAsteroid(p, rotation);
    }
};

#endif /* rocks_hpp */
