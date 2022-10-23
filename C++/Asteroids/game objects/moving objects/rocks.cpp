//
//  rocks.cpp
//  Asteroids
//
//  Created by Elijah Harrison on 11/14/20.
//

#include "rocks.hpp"

void Rock::initializeRotation() {
    da = random(ROCK_ROTATE_SPEED/2, ROCK_ROTATE_SPEED);
}

// TODO: change these from being hard coded values to variables
void Rock::initializePosition() {
    p.setX(random(-500.0, 500.0));
    p.setY(random(-500.0, 500.0));
}

void Rock::initializePosition(Point pInit) {
    p.set(pInit);
}

void Rock::initializeVelocity() {
    std::cout << "Rock::initializeVelocity()\n";
    // launch in random direction
    v.applyForce(ROCK_INIT_LAUNCH_FORCE, mass, Trig::rad(random(0, 360)));
}

void Rock::initializeVelocity(Velocity vInit) {
    std::cout << "Rock::initializeVelocity(Velocity vInit) called.\n";

    // if non-default velocity, add it to our current v
    if (abs(v.getSpeed()) > 0) v.add(vInit);
    
    // if default velocity, launch in random direction
    else initializeVelocity(); // call default initializeVelocity() to do this
}
