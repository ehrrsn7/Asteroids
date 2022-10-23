/**********************************************************************
 * Header File: Vector
 **********************************************************************/

#pragma once

#include <iostream>
#include <cassert>
#include <cmath> // for sin/cos (for now until physicsFormulas.h is done)

/**************************************************
 * forward declarations/prototypes
 **************************************************/
class Vector;
class Position;
class Velocity;
class Acceleration;
class Force;
class Gravity;
class Trig;
class TestPosition;

/**************************************************
 * CLASS Vector
 *    Base class for all classes with a need for
 *    an x and y component.
 **************************************************/
class Vector {
public:
   /**************************************************
    * Constructors
    **************************************************/
   Vector() : Vector(0.0, 0.0) { }              // default constructor
   Vector(double x, double y)  : x(x), y(y) { } // non-default constructor
   Vector(const Vector & s)    { *this = s; }   // copy constructor
   Vector & operator = (const Vector & rhs);    // assignment operator '='
   
   /**************************************************
    * Getters
    **************************************************/
   double getX() const { return x; }
   double getY() const { return y; }
   
   /**************************************************
    * Setters
    **************************************************/
   void setX(double x) { this->x = x; }
   void setY(double y) { this->y = y; }
   
   void set(double x, double y);
   void set(const Vector & s) { set(s.getX(), s.getY()); }
   
   /**************************************************
    * Adders
    **************************************************/
   void addX(double dx) { setX(getX() + dx); }
   void addY(double dy) { setY(getY() + dy); }
   
   void add(double dx, double dy);
   void add(const Vector & v);
   
   /**************************************************
    * Other Getters/Setters
    **************************************************/
   double getMagnitude() const;
   double getAngleRadians() const { return atan2(getX(), getY()); }
   double angle() const           { return getAngleRadians(); }
   static Vector forward(double angleRadians);

   void setPolar(double magnitude, double angleRadians);
   void setMagnitude(double magnitude, double angleRadians); // just an alias for setPolar
   void setMagnitudeAngle(double m, double a) { setMagnitude(m, a); }
   
   void addPolar(double magnitude, double angleRadians);
   void addMagnitude(double magnitude, double angleRadians); // "
   
   /**************************************************
    * Operators
    **************************************************/
   Vector operator + (const Vector & rhs);
   Vector & operator += (const Vector & rhs);
   
   /**************************************************
    * Helpers
    **************************************************/
   void print() { std::cout << this; }

protected:
   double x; // horizontal position (meters)
   double y; // vertical position (meters)
   
   friend class TestVector;
};

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Vector & rhs);
std::istream & operator >> (std::istream & in,        Vector & rhs);

/**************************************************
 * CLASS Position
 * A single position on the field in Meters.
 * Position is responsible for keeping track of
 * both the meters representation of the
 * Simulator and the pixels drawn to the screen
 * via the ogstream object.
 **************************************************/
class Position : public Vector {
public:
   Position() : Vector(0.0, 0.0) { }                // default constructor
   Position(bool) { }                               // debug
   Position(double x, double y)  : Vector(x, y) { } // non-default constructor
   Position(const Position & pt) { *this = pt; }    // copy constructor
   Position(const Vector & s)    { *this = s; }     // polymorphic copy
   Position & operator = (const Position & rhs);    // assignment operator '='
   Position & operator = (const Vector & rhs);      // polymorphic assignment
   
   double getMetersX() const { return getX(); }
   double getMetersY() const { return getY(); }
   double getPixelsX() const { return getMetersX() / metersFromPixels; }
   double getPixelsY() const { return getMetersY() / metersFromPixels; }
   
   static Position forward(double angleRadians);

   double metersToPixels(double meters) { return meters / Position::metersFromPixels; }
   double pixelsToMeters(double pixels) { return pixels * Position::metersFromPixels; }

   void set(double x, double y) { Vector::set(x, y); }
   void set(const Position & p) { Vector::set(p.getX(), p.getY()); }
   void setXY(double x, double y) { Vector::set(x, y); }
   void setMetersX(double xMeters) { setX(xMeters); }
   void setMetersY(double yMeters) { setY(yMeters); }
   void setMeters(double xMeters, double yMeters);
   void setMetersPolar(double magnitudeMeters, double angleRadians);
   void setPixelsX(double xPixels) { setMetersX(xPixels * metersFromPixels); }
   void setPixelsY(double yPixels) { setMetersY(yPixels * metersFromPixels); }
   void setPixels(double xPixels, double yPixels);
   
   void add(const Position & p) { Vector::add(p.getX(), p.getY()); }
   void add(const Velocity & dv, double dt);
   void addPixelsX(double dxPixels) { setPixelsX(getPixelsX() + dxPixels);  }
   void addPixelsY(double dyPixels) { setPixelsY(getPixelsY() + dyPixels);  }
   void addPixels(double dxPixels, double dyPixels);
   void addMetersX(double dxMeters) { setMetersX(getMetersX() + dxMeters); }
   void addMetersY(double dyMeters) { setMetersY(getMetersY() + dyMeters); }
   void addMeters(double dxMeters, double dyMeters);
   
   double getZoom() const { return metersFromPixels; }
   void setZoom(double metersFromPixels);
   
   Position operator + (const Position & rhs) const;
   Position & operator += (const Position & rhs);
   
   Position operator - (const Position & rhs); // subtraction
   Position operator - (); // negative
   
private:
   static double metersFromPixels;
   friend class TestPosition;
};

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Position & rhs);
std::istream & operator >> (std::istream & in,        Position & rhs);

// simple struct to provide equivalent of class structure without the overhead
struct PT {
   int x;
   int y;
};

/**************************************************
 * CLASS Velocity
 * A change in Position.
 **************************************************/
class Velocity : public Vector {

// to not overcomplicate things, let's rely on Vector's get/set components
// for our getters/setters in the child classes:

// getX()       | substitutes get 'dx'
// getY()       | substitutes get 'dy'
// magnitude()  | substitutes get speed
    
public:
   // constructors
   Velocity() : Vector(0.0, 0.0) { }               // default constructor
   Velocity(double x, double y) : Vector(x, y) { } // non-default constructor
   Velocity(const Velocity & v) { *this = v; }     // copy constructor
   Velocity(const Vector & s)   { *this = s; }     // polymorphic copy
   Velocity & operator = (const Velocity & rhs);   // assignment operator '='
   Velocity & operator = (const Vector & rhs);     // polymorphic assignment
   
   // get
   static Velocity forward(double angleRadians);
   double getSpeed() const { return getMagnitude(); }
   double getDx() const    { return getX(); }
   double getDy() const    { return getY(); }

   // set
   void set(double x, double y) { Vector::set(x, y); }
   void set(const Velocity & v) { Vector::set(v.getX(), v.getY()); }
   void setDx(double dX)        { setX(dX); }
   void setDy(double dY)        { setX(dY); }
   
   // add
   void add(const Velocity & dv);
   
   // operators
   Velocity operator + (const Velocity & rhs) const;
   Velocity & operator += (const Velocity & rhs);
   Position operator * (const double rhs);
   
private:
   // helper methods
   Position toPosition(const double dt);
  
   friend class TestVelocity;
};

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Velocity & rhs);
std::istream & operator >> (std::istream & in,        Velocity & rhs);

/**************************************************
 * CLASS Acceleration
 * A change in Velocity.
 **************************************************/
class Acceleration : public Vector {
    
public:
   // constructors
   Acceleration() : Vector(0.0, 0.0)    { }                // default constructor
   Acceleration(double x, double y)     : Vector(x, y) { } // non-default constructor
   Acceleration(const Acceleration & a) { *this = a; }     // copy constructor
   Acceleration(const Vector & s)       { *this = s; }     // polymorphic copy
   Acceleration & operator = (const Acceleration & rhs);   // assignment operator '='
   Acceleration & operator = (const Vector & rhs);         // polymorphic assignment
   
   // get
   static Acceleration forward(double angleRadians);

   // set
   void set(double x, double y) { Vector::set(x, y); }
   void set(const Acceleration & a) { Vector::set(a.getX(), a.getY()); }
   
   // add
   void add(const Acceleration & da);
   
   // operators
   Acceleration operator + (const Acceleration & rhs);
   Acceleration & operator += (const Acceleration & rhs);
   Velocity operator * (const double rhs);
   
private:
   // helper methods
   Velocity toVelocity(const double dt);
   
   friend class TestAcceleration;
};

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Acceleration & rhs);
std::istream & operator >> (std::istream & in,        Acceleration & rhs);

/**************************************************
 * CLASS Force
 * Acceleration integrated by mass.
 **************************************************/
class Force : public Vector {
   
public:
   // constructors
   Force() : Vector(0.0, 0.0) { }               // default constructor
   Force(double x, double y) : Vector(x, y) { } // non-default constructor
   Force(const Force & f)    { *this = f; }     // copy constructor
   Force(const Vector & s)   { *this = s; }     // polymorphic copy
   Force & operator = (const Force & rhs);      // assignment operator '='
   Force & operator = (const Vector & rhs);     // polymorphic assignment
   
   // get
   static Force forward(double angleRadians);
   
   // set
   void set(double x, double y) { Vector::set(x, y); }
   void set(const Force & f) { Vector::set(f.getX(), f.getY()); }
   
   // add
   void add(const Force dF);
   
   // operators
   Force operator + (const Force & rhs);
   Force & operator += (const Force & rhs);
   Acceleration operator / (const double rhs);
   
private:
   // helper methods
   Acceleration toAcceleration(double mass) const {
      return Acceleration(getX() / mass, getY() / mass);
   }
   
   friend class TestForce;
};

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Force & rhs);
std::istream & operator >> (std::istream & in,        Force & rhs);

/**************************************************
 * CLASS Gravity
 * A special kind of force which describes
 * force due to gravity.
 **************************************************/
class Gravity : public Force {
   
public:
   // constructors
   Gravity() : Force(0.0, 0.0) { }                 // default constructor
   Gravity(double x, double y) : Force(x, y) { }   // non-default constructor
   Gravity(const Gravity & g)  { *this = g; }      // copy constructor
   Gravity & operator = (const Gravity & rhs);     // assignment operator '='
   Gravity & operator = (const Vector & rhs);      // polymorphic assignment
   
   // get
   static Gravity forward(double angleRadians);
   
   // set
   void set(double x, double y) { Vector::set(x, y); }
   void set(const Gravity & g) { Vector::set(g.getX(), g.getY()); }
   
   // add
   void add(const Gravity dF);
   
   // operators
   Gravity operator + (const Gravity & rhs);
   Gravity & operator += (const Gravity & rhs);
   Acceleration operator / (const double rhs);
   
private:
   // helper methods
   Acceleration toAcceleration(double mass) const {
      return Acceleration(getX() / mass, getY() / mass);
   }
   
   friend class TestGravity;
};

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Gravity & rhs);
std::istream & operator >> (std::istream & in,        Gravity & rhs);

class Trig {
public:
   const static double deg(double);
   const static double rad(double);
   const static double mag(const Vector &);
   const static double getMagnitude(const Vector &);
   const static double mag(double, double);
   const static double getMagnitude(double, double);
};
