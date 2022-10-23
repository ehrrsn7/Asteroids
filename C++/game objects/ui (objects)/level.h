//
//  level.h
//  Asteroids
//
//  Created by Elijah Harrison on 11/7/20.
//

#ifndef level_hpp
#define level_hpp

#include <iostream>
#include "../../vector/vector.h"
#include "../../ui/uiDraw.h"

class Level {

private:
    int level;
    Position position;

public:
    Level() {
        std::cout << "Level constructor called." << std::endl;
        level = 1;
    }
    
    void set(Position p) { position.set(p); }
    
    void display() {
        // TODO: not displaying properly.
        std::string levelText = "Level: ";
        levelText += std::to_string(level);
        drawText(position, levelText.c_str());
    }
    
    void next() { level += 1; }
    void reset() { level = 1; }
};

#endif /* level_hpp */
