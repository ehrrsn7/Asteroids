//
//  score.h
//  Asteroids
//
//  Created by Elijah Harrison on 11/7/20.
//

#ifndef score_hpp
#define score_hpp

#include <iostream>
#include <string>

#include "../../vector/vector.h"
#include "../../ui/uiDraw.h"

class Score {

private:
    int score;
    Position position;

public:
    Score() {
        std::cout << "Score constructor called." << std::endl;
        score = 0;
    }
    
    void set(Position p) { position.set(p); }
    
    void display() {
        std::string scoreText = "Score: ";
        scoreText += std::to_string(score);
        drawText(position, scoreText.c_str());
    }
    
    void add(int dPoints) { score += dPoints; }
    void reset() { score = 0; }
};

#endif /* score_hpp */
