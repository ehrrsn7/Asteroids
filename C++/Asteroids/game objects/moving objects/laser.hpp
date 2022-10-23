//
//  laser.hpp
//  Asteroids
//
//  Created by Elijah Harrison on 11/8/20.
//

#ifndef laser_hpp
#define laser_hpp

#import <iostream>
#import "movingObject.hpp"
#import "point.hpp"
#import "velocity.hpp"
#import "uiDraw.hpp"

#define FIRE_DELAY_TIME .05 // laser firing rate delay in seconds
#define LASER_SPEED 10 // speed in pixels/frame
#define LASER_DEATH_TIME 20 // laser expiration time in seconds / 4
#define LASER_MASS 5 // kg

#define ALIVE true
#define DEAD false

class Laser : public MovingObject {
public:
    Laser(float firingAngle, Point shipPoint, Velocity shipVelocity, float shipRadius) {
        // initialize
        name = "Laser";
        gameObjectID = laser;

        // fire laser
        setPoint(shipPoint); // initialize at ship's position
        p.add(Velocity::forward(firingAngle) * shipRadius * 6); // offset to front of ship
        setVelocity(Velocity::forward(firingAngle) * LASER_SPEED); // fire!!
        setDeathTimer(LASER_DEATH_TIME); // set to expire after desired amount (LASER_DEATH_TIME)
        
        // debug
        // std::cout << "Laser constructor called.";
        // std::cout << " v "; v.print();
        // std::cout << " p "; p.print();
        // std::cout << std::endl;
    }
    
    void display() {
        drawDot(p);
    }
};

#endif /* laser_hpp */
