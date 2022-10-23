//
//  level.hpp
//  Asteroids
//
//  Created by Elijah Harrison on 11/7/20.
//

#ifndef level_hpp
#define level_hpp

#include <iostream>
#include "point.hpp"
#include "uiDraw.hpp"

class Level {

private:
    int level;
    Point position;

public:
    Level() {
        std::cout << "Level constructor called." << std::endl;
        level = 1;
    }
    
    void set(Point p) { position.set(p); }
    
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
