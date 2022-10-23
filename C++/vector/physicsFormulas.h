/**********************************************************************
 * physicsFormulas.h
 * orbitSimulator
 **********************************************************************/

#pragma once

#define FPS 30                // frames/s
#define SECONDS_IN_DAY 86400  // s : 60s/min * 60min/hr * 24hr/d

#include "vector.h" // for Vector/child classes 

/**************************************************
 * Prototypes
 **************************************************/
class MovingObject;
class Earth;

namespace formulas {

/**********************************************************************
 * Horizontal/Vertical Components
 **********************************************************************/
double trigX(const double mag, const double angleRadians);
double trigY(const double mag, const double angleRadians);
 
double trigX(const Vector & v);
double trigY(const Vector & v);

double mag(double x, double y);
double mag(const Vector & s);
double deg(double angleRadians);
double rad(double angleDegrees);

/**********************************************************************
* Distance Functions
**********************************************************************/
double distance(const Position & pos1, const Position & pos2);
double distance(const MovingObject & obj1, const MovingObject & obj2);
double computeDistance(const Position & pos1, const Position & pos2);
bool hasCollided(MovingObject & obj1, MovingObject & obj2);

/**********************************************************************
 * Time Functions
 **********************************************************************/
double timeDilation();
double dilateTime(double dt);
double timePerFrame();

/**********************************************************************
 * Pixels to meters/reverse conversions
 **********************************************************************/
double pixelsToMeters(double pixels);
double metersToPixels(double meters);
 
/**********************************************************************
 * Earth Functions
 **********************************************************************/
double earthRotationSpeed();
double earthRotationSpeed(double dt);

/**********************************************************************
* Gravity Functions
**********************************************************************/
double calcHeight(const Position & p);
double directionOfGravity(const Position & p1, const Position & p2);
double directionOfGravity(const MovingObject & obj1, const MovingObject & obj2);
Gravity forceDueToGravity(const MovingObject & obj1, const MovingObject & obj2);
double calcGravity(double height);
Acceleration calcGravityVector(const Position & p);

/**********************************************************************
 * Motion
 **********************************************************************/
double aToD(const Acceleration & a, const Velocity & v0, double dt, double initialD);
double aToX(const Acceleration & a, const Velocity & v0, double dt, double initialD);
double aToY(const Acceleration & a, const Velocity & v0, double dt, double initialD);
double aToDx(const Acceleration & a, const Velocity & v0, double dt);
double aToDy(const Acceleration & a, const Velocity & v0, double dt);
Velocity aToV(const Acceleration & a, const Velocity & v0, const double dt);

};
