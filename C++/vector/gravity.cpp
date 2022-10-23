/**********************************************************************
 * gravity.cpp
 * orbitSimulator
 **********************************************************************/

#include "vector.h"

#include "physicsFormulas.h"

/**************************************************
 * Methods
 **************************************************/
Gravity Gravity::forward(double angleRadians) {
   return Gravity(formulas::trigX(1.0, angleRadians), formulas::trigY(1.0, angleRadians));
}

// add
void Gravity::add(const Gravity dF) {
   Vector::add(dF.getX(), dF.getY());
}

// operators
Gravity Gravity::operator + (const Gravity & rhs) { // rhs : ΔG
   Gravity newG = *this;
   newG.add(rhs);
   return newG;
}

Gravity & Gravity::operator += (const Gravity & rhs) { // rhs : ΔG
   add(rhs);
   return *this;
}

Acceleration Gravity::operator / (const double rhs) { // rhs : mass
   return toAcceleration(rhs);
}

Gravity & Gravity::operator = (const Gravity & rhs) {
   Vector::set(rhs.getX(), rhs.getY());
   return *this;
}

Gravity & Gravity::operator = (const Vector & rhs) {
   Vector::set(rhs);
   return *this;
}

/**************************************************
 * GRAVITY ostream insertion
 **************************************************/
std::ostream& operator << (std::ostream& out, const Gravity& rhs) {
   out << "(" << rhs.getX() << "N , " << rhs.getY() << "N)";
   return out;
}
   
/**************************************************
 * GRAVITY istream extraction
 **************************************************/
std::istream& operator >> (std::istream& in, Gravity& rhs) {
   double x, y;
   in >> x >> y;
   rhs.set(x, y);
   return in;
}
