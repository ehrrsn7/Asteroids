//
//  ship.hpp
//  Asteroids
//
//  Created by Elijah Harrison on 11/7/20.
//

#ifndef ship_hpp
#define ship_hpp

#include <stdio.h>
#include <string>

#include "movingObject.hpp"
#include "laser.hpp"
#include "uiDraw.hpp"
#include "uiInteract.hpp" // for rotation directions' int values

#define SHIP_ROTATE_AMOUNT 15 // in rad/s
#define SHIP_ACCELERATE_AMOUNT 2
#define SHIP_SPEED_LIMIT 15 // pixels per second
#define SHIP_BRAKES_AMOUNT 1
#define SHIP_FRICTION_AMOUNT .1
#define SHIP_MASS 200 // kg
#define SHIP_MAX_SPEED 50 // px/s

class Ship : public MovingObject {
    
protected:
    Velocity brakesAmount;
    Velocity frictionAmount;
    float laserFiringDelayTimer;
    
public:
    Ship() {
        name = "Player Ship";
        std::cout << std::endl << name << " constructor called.\n";
        thrust = SHIP_ACCELERATE_AMOUNT;
        setRadius(2);
        rotation += M_PI/2;
        friction = true;
        std::cout << friction << std::endl << std::endl;
        brakesAmount = Velocity();
        frictionAmount = Velocity();
        laserFiringDelayTimer = 0.0;
    }
    
    void display() override {
        drawShip(p, Trig::deg(rotation) - 90, getRadius());
    }
    
    void update() {
        MovingObject::update(); // call parent method before anything else
        if (!alive) return; // quick exit
        
        // apply brakes/friction
        if (brake) {
            brakesAmount.setDx(-v.getDx() * SHIP_BRAKES_AMOUNT / 10);
            brakesAmount.setDy(-v.getDy() * SHIP_BRAKES_AMOUNT / 10);
            v.add(brakesAmount);
            std::cout << "brakes applied "; brakesAmount.print(); std::cout << std::endl; // debug brakes
        }
        brake = false; // only apply brakes on frames where applyBrake() was called
        
        if (friction) {
            frictionAmount.setDx(-v.getDx() * SHIP_FRICTION_AMOUNT / 10);
            frictionAmount.setDy(-v.getDy() * SHIP_FRICTION_AMOUNT / 10);
            v.add(frictionAmount);
            // std::cout << "friction applied "; frictionAmount.print(); std::cout << std::endl; // debug friction
        }
        
        // decrement laser firing delay timer
        updateLaserFiringDelayTimer();
        
        // limit speed
        if (v.getSpeed() > SHIP_MAX_SPEED) {
            std::cout << "Max speed (" << SHIP_MAX_SPEED << ") reached.\n";
            applyBrakes();
        }
    }
    
    void rotate(int direction) {
        if (!alive) return; // quick exit
        // std::cout << "rotating " << direction << std::endl; // debug
        // std::cout << "rotation: (" << rotation << ")\n";
        
        if (direction == LEFT) {
            // std::cout << "turn left" << std::endl;
            setRotation(SHIP_ROTATE_AMOUNT);
        }

        if (direction == RIGHT) {
            // std::cout << "turn right" << std::endl;
            setRotation(-SHIP_ROTATE_AMOUNT);
        }

        // ** LEFT/RIGHT defined in keys enum in uiInteract.hpp
    }
    
    void stopRotating() {
        // std::cout << "stop turning" << std::endl;
        setRotation(0.0);
    }
    
    void applyBrakes() { brake = true; }
    
    Laser fire() { return Laser(rotation, p, v, r); }
    
    float getLaserFiringDelayTimer() const {
        return laserFiringDelayTimer;
    }
    void setLaserFiringDelayTimer() {
        laserFiringDelayTimer = FIRE_DELAY_TIME; // from laser.hpp
    }
    void updateLaserFiringDelayTimer() {
        if (laserFiringDelayTimer >= 0.0) {
            laserFiringDelayTimer -= 1.0/FPS;
            // std::cout << "laserFiringDelayTimer: " << laserFiringDelayTimer << std::endl; // debug
        }
    }
};

#endif /* ship_hpp */
