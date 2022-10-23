//
//  rocks.cpp
//  Asteroids
//
//  Created by Elijah Harrison on 11/14/20.
//

#include "rocks.h"

void Rock::initializeRotation() {
    da = random(ROCK_ROTATE_SPEED/2, ROCK_ROTATE_SPEED);
}

// TODO: change these from being hard coded values to variables
void Rock::initializePosition() {
    p.setX(random(-500.0, 500.0));
    p.setY(random(-500.0, 500.0));
}

void Rock::initializePosition(Position pInit) {
    p.set(pInit);
}

void Rock::initializeVelocity() {
   std::cout << "Rock::initializeVelocity()\n";
   // launch in random direction
   double dt = 1.0;
   Force initialForce = Force();
   initialForce.setPolar(ROCK_INIT_LAUNCH_FORCE, random(0, 360));
   v = (initialForce / mass) * dt;
}

void Rock::initializeVelocity(Velocity vInit) {
    std::cout << "Rock::initializeVelocity(Velocity vInit) called.\n";

    // if non-default velocity, add it to our current v
    if (abs(v.getMagnitude()) > 0) v.add(vInit);
    
    // if default velocity, launch in random direction
    else initializeVelocity(); // call default initializeVelocity() to do this
}
