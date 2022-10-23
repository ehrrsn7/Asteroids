//
//  movingObject.cpp
//  Asteroids
//
//  Created by Elijah Harrison on 11/7/20.
//

#include "movingObject.h"

void MovingObject::displayDebugUpdateInfo() {
    std::cout << name << ".update() :: ";
    std::cout << "p.add(v)";
    std::cout << "\t// v: ";
    v.print();
    std::cout << "\t// p: ";
    p.print();
    std::cout << "   ";
}

void MovingObject::setDeathTimer(double duration) {
    timer = duration;
    timerOn = true;
    // std::cout << "Laser death timer set to " << duration << std::endl; // debug
}

void MovingObject::accelerate() {
    if (!alive) return; // quick exit
    v.add(v.forward(rotation) * thrust);
}

void MovingObject::hit() {
    setAlive(false);
    std::cout << name << ".hit() " << std::endl;
}
