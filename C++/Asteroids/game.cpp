//
//  game.cpp
//  Asteroids
//
//  Created by Elijah Harrison on 11/7/20.
//

#include "game.hpp"

#include <limits> // for getClosestDistance()
#include <algorithm>

// initialization
void Game::setUpScreen(Point tl, Point br) {
    center.setXY(0, 0); // center of screen
    screenLeft   = tl.getX();
    screenRight  = br.getX();
    screenBottom = br.getY();
    screenTop    = tl.getY();
    score.set(Point(screenLeft + 10, screenTop - 15));
    level.set(Point(screenRight - 55, screenTop - 15));
    
    std::cout << "Screen left:  " << screenLeft << std::endl;
    std::cout << "Screen right: " << screenRight << std::endl;
    std::cout << "Screen up:    " << screenTop << std::endl;
    std::cout << "Screen down:  " << screenBottom << std::endl;
}

void Game::fireLaser() {
    // handle "machine gun firing here"
    // define firing rate above
    // (at desired rate:)
    // get new laser from ship->fire()
    // push new laser onto lasers (vector<>)
    if (ship->getLaserFiringDelayTimer() <= 0) {
        lasers.push_back(ship->fire());
        ship->setLaserFiringDelayTimer();
    }
}

float dist(Point & p1, Point & p2) {
    return sqrt((p1.getX() * p1.getX()) + (p2.getX() * p2.getX()));
}

Rock* Game::createRock(int whichRock, Point pInit, Velocity vInit, bool isInitial) {
    
    /* initialize p and v */
    
    // condition: don't randomize if pInit is non-default
    if (Trig::getMagnitude(pInit.getX(), pInit.getY()) < 10) {
        
        // default v randomized in individual rock constructors
        // default p [aka Point(0,0)] set to random location:
        float newX = random(screenLeft, screenRight);
        float newY = random(screenBottom, screenTop);
        pInit.setXY(newX, newY);
    
        /* handle ship—rock buffer */
        
        // condition: only on initialization
        if (isInitial) {
        
            // error condition: ship has not been created (should not happen)
            if (ship != NULL) { // if ship is null (error), then skip
                
                Point shipPoint = ship->getPoint();
                float buffer = 100;

                // while dist(rock, ship) < buffer, then REDO RANDOM POINT
                while (dist(shipPoint, pInit) < buffer) { // redo random point
                    std::cout << ">>> newRock.p within buffer @ ("
                        << newX << ", "
                        << newY << ")"
                        << ", recalculate." << std::endl;
                    newX = random(screenLeft, screenRight);
                    newY = random(screenBottom, screenTop);
                    pInit.setXY(newX, newY);

                } // end while rock within buffer radius
            } // end if ship != NULL
        } // end if isInitial
    } // end if pInit != default P(0,0)
    
    // create new rock
    Rock* newRock = NULL;
    switch(whichRock) {
        case bigRock:
            newRock = new BigRock(pInit, vInit);
            break;
        case mediumRock:
            newRock = new MediumRock(pInit, vInit);
            break;
        case smallRock:
            newRock = new SmallRock(pInit, vInit);
            break;
    }
    return newRock;
}

void Game::asteroidBelt() {
    for (int i = 0; i < Rock::amountInit; i++) {
        std::cout << std::endl << "asteroid belt " << i << " ";
        Point pInit;
        Velocity vInit;
        rocks.push_back(createRock(bigRock, pInit, vInit, true));
    }
}

void Game::wrap(MovingObject* obj) {
    bool debug = false;
    if (debug) printf("wrap() called ");
    float buffer = obj->getRadius() + 10;

    /* SCREEN SIDE VALS REFERENCE
     * screen left   == topLeft.getX() - obj->getRadius()
     * screen right  == bottomRight.getX() + obj->getRadius()
     * screen bottom == bottomRight.getY() - obj->getRadius()
     * screen top    == topLeft.getY() + obj->getRadius()
     */

    // obj x < screen left => screen right
    if (obj->getPoint().getX() < screenLeft - buffer) {
        obj->setPointX(screenRight + buffer);
        if (debug) printf("//  Wrap left -> right");
    }
    
    // obj x > screen right => screen left
    else if (obj->getPoint().getX() > screenRight + buffer) {
        obj->setPointX(screenLeft - buffer);
        if (debug) printf("//  Wrap right -> left");
    }
    
    // obj y < screen bottom => screen top
    if (obj->getPoint().getY() < screenBottom - buffer) {
        obj->setPointY(screenTop + buffer);
        if (debug) printf("//  Wrap bottom -> top");
    }
    
    // obj y > screen top => screen bottom
    else if (obj->getPoint().getY() > screenTop + buffer) {
        obj->setPointY(screenBottom - buffer);
        if (debug) printf("//  Wrap top -> bottom");
    }
    
    if (debug) printf("\n");
}

void Game::wrapObjects() {
    int i = 0;

    // wrap ship
    if (ship != NULL) wrap(ship);

    // wrap lasers
    for (std::vector<Laser>::iterator it = lasers.begin(); it < lasers.end(); ++it, ++i) {
        wrap(&lasers[i]);
    }
    i = 0;

    // wrap rocks
    for (std::vector<Rock*>::iterator it = rocks.begin(); it < rocks.end(); ++it, ++i) {
        if ((*it) == NULL) break; // just in case
        wrap(rocks[i]);
    }
}

void Game::handleCollisions() {
    // std::cout << "Game::handleCollisions();\n"; // debug

    // skip this method if ship is no longer alive
    if (ship == NULL) return;
    if (!ship->isAlive()) return;
    
    // handle collisions here
    
    // for each rock
    auto rit = rocks.begin(); while (rit < rocks.end()) {
        if ((*rit) == NULL) break; // just in case
        // std::cout << "check rock collision" << std::distance(rocks.begin(), rit) << std::endl;
        
        // ship
        if (checkCollision(ship, (*rit))) {
            splitRock(**rit, *ship);
            if ((*rit) != NULL) (*rit)->hit(); // hit rock
            score.add((*rit)->getScoreAmount()); // handle score
            ship->hit(); // hit ship
            return; // ignore the rest to prevent bugs
        }
        
        // for each laser
        auto lit = lasers.begin(); while (lit < lasers.end()) {

            if (checkCollision(&(*lit), (*rit))) {
                splitRock(**rit, *lit);
                if ((*rit) != NULL) (*rit)->hit(); // hit rock
                score.add((*rit)->getScoreAmount()); // handle score
                lit->hit(); // hit laser
                return; // ignore the rest to prevent bugs
            }
            
            ++lit; // iterate lasers
        }
        ++rit; // rocks iterator
    }
}

std::pair<Velocity, Velocity> generateOffsetVelocity(MovingObject rock, MovingObject obj) {
    // generate offset velocity between rocks
    // we don't want the split rocks to continue on same point
    
    // rules for new velocity:
    // - needs to be within 15° of normal to initial velocity
    // - offset speeds depend on size of rock (get info from rocks.hpp based on rockID)

    // get total mass/momentum information
    float totalMomentum = rock.getMomentum() + obj.getMomentum();
    float totalMass     = rock.getMass()     + obj.getMass();

    // get final speed/angleRadians from mass/momentum info
    float finalSpeed = totalMomentum / totalMass; // velocity = ρ / m
    float finalAngle = (
        obj.getVelocity().getAngleRadians() +
        rock.getVelocity().getAngleRadians()) / 2;

    // get angle deviance from finalAngle, randomly calculated between 0° and 15°
    float randomAngleOffset = Trig::rad(random(0, 15)); // = ø

    // set final velocities of new rocks based on final speed, angle and ø offset
    Velocity offsetVelocity1, offsetVelocity2;
    offsetVelocity1.setMagnitudeAngle(finalSpeed, finalAngle - randomAngleOffset);
    offsetVelocity2.setMagnitudeAngle(finalSpeed, finalAngle + randomAngleOffset);
    
    // package and return
    return std::pair<Velocity, Velocity>(offsetVelocity1, offsetVelocity2);
}

void Game::splitRock(Rock & rock, MovingObject & obj) {
    std::cout << "splitRock(*" << rock.getName() << ");\n"; // debug
    
    // create index to identify which rocks which will be split into
    int newRockIndex = rock.getNextRockIndex();
    
    /* do what the good book says */
    // Create 2 pointers for new rocks, set them to null
    Rock* newRock1 = NULL;
    Rock* newRock2 = NULL;
    
    // generate offset velocity between rocks
    auto offsetVelocityPair = generateOffsetVelocity(rock, obj);
    Velocity offsetV1 = offsetVelocityPair.first; // unpack
    Velocity offsetV2 = offsetVelocityPair.second;
    
    // Create the new Rock ptrs
    newRock1 = createRock(
        newRockIndex, rock.getPoint(), rock.getVelocity() + offsetV1, false);
    newRock2 = createRock(
        newRockIndex, rock.getPoint(), rock.getVelocity() + offsetV2, false);

    // add them to vector<Rock*>
    rocks.push_back(newRock1);
    rocks.push_back(newRock2);
}

bool Game::checkCollision(MovingObject* obj1, MovingObject* obj2) {
    // std::cout << "checkCollision(*" << obj1->getName() << ", *" << obj2->getName() << ");\n";
    
    float tooClose = obj1->getRadius() + obj2->getRadius();

    if (getClosestDistance(*obj1, *obj2) < tooClose) {
        std::cout << "collision between " << obj1->getName() << " and " << obj2->getName() << std::endl;
        return true;
    } else return false;
}

float Game::getClosestDistance(const MovingObject &obj1, const MovingObject &obj2) {
    // find the maximum distance traveled
    float dMax = std::max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
    dMax = std::max(dMax, abs(obj2.getVelocity().getDx())); // Between previous max and |obj2.dx|
    dMax = std::max(dMax, abs(obj2.getVelocity().getDy())); // Between previous max and |obj2.dy|
    dMax = std::max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.

    float distMin = std::numeric_limits<float>::max();
    for (float i = 0.0; i <= dMax; i++) {
        Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
        Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));

        float xDiff = point1.getX() - point2.getX();
        float yDiff = point1.getY() - point2.getY();

        float distSquared = (xDiff * xDiff) +(yDiff * yDiff);

        distMin = std::min(distMin, distSquared);
    }

    return sqrt(distMin);
}

void Game::cleanUpZombies() {
    cleanUpShip();
    cleanUpRocks();
    cleanUpLasers();
}

void Game::cleanUpShip() {
    if (ship != NULL)
        if (!ship->isAlive())
            ship = NULL;
}

void Game::cleanUpLasers() {
    std::vector<Laser>::iterator it = lasers.begin();
    while (it != lasers.end()) {
        if (!(*it).isAlive()) {
            it = lasers.erase(it);
            return;
        }
        else ++it;
    }
}

void Game::cleanUpRocks() {
    std::vector<Rock*>::iterator it = rocks.begin();
    while (it != rocks.end()) {
        if ((*it) == NULL) break; // just in case
        if (!(*it)->isAlive()) {
            std::cout << "removing " << (*it)->getName() << std::endl;
            it = rocks.erase(it);
            return;
        }
        else ++it;
    }
}

void Game::reset() {
    resetShip();
    removeAllLasers();
    resetAllRocks();
    resetScore();
}

void Game::resetShip() {
    Ship * newShip = NULL;
    newShip = new Ship();
    ship = newShip;
}

void Game::resetAllRocks() {
    removeAllRocks();
    asteroidBelt();
}

void Game::removeAllRocks() {
    std::vector<Rock*>::iterator it = rocks.begin();
    while (it != rocks.end()) it = rocks.erase(it);
}

void Game::removeAllLasers() {
    std::vector<Laser>::iterator it = lasers.begin();
    while (it != lasers.end()) it = lasers.erase(it);
}

void Game::resetScore() {
    score.reset();
}
