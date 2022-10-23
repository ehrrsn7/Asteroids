/**********************************************************************
 * force.cpp
 * orbitSimulator
 **********************************************************************/

#include "vector.h"

#include "physicsFormulas.h"

/**************************************************
 * Methods
 **************************************************/
Force Force::forward(double angleRadians) {
   return Force(formulas::trigX(1.0, angleRadians), formulas::trigY(1.0, angleRadians));
}

void Force::add(const Force dF) {
   Vector::add(dF.getX(), dF.getY());
}

Force Force::operator + (const Force & rhs) { // rhs : ΔF
   Force newF = *this;
   newF.add(rhs);
   return newF;
}

Force & Force::operator += (const Force & rhs) { // rhs : ΔF
   add(rhs);
   return *this;
}

Acceleration Force::operator / (const double rhs) { // rhs : mass
   return toAcceleration(rhs);
}

Force & Force::operator = (const Force & rhs) {
   Vector::set(rhs.getX(), rhs.getY());
   return *this;
}

Force & Force::operator = (const Vector & rhs) {
   Vector::set(rhs);
   return *this;
}

/**************************************************
 * FORCE ostream insertion
 **************************************************/
std::ostream& operator << (std::ostream& out, const Force& rhs) {
   out << "(" << rhs.getX() << "N , " << rhs.getY() << "N)";
   return out;
}
   
/**************************************************
 * FORCE istream extraction
 **************************************************/
std::istream& operator >> (std::istream& in, Force& rhs) {
   double x, y;
   in >> x >> y;
   rhs.set(x, y);
   return in;
}
