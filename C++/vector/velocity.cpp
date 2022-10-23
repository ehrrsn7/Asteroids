/**********************************************************************
 * velocity.cpp
 * orbitSimulator
 **********************************************************************/

#include "vector.h"

#include "physicsFormulas.h"

/**************************************************
 * Methods
 **************************************************/
Velocity Velocity::forward(double angleRadians) {
   return Velocity(formulas::trigX(1.0, angleRadians), formulas::trigY(1.0, angleRadians));
}

void Velocity::add(const Velocity & dv) {
   Vector::add(dv.getX(), dv.getY()); // call parent add
}

Velocity Velocity::operator + (const Velocity & rhs) const { // rhs : Δt
   return Velocity(x + rhs.x, y + rhs.y);
}

Velocity & Velocity::operator += (const Velocity & rhs) { // rhs : Δt
   add(rhs);
   return *this;
}

Position Velocity::toPosition(const double dt) {
   return Position(getX() * dt, getY() * dt);
}

Position Velocity::operator * (const double rhs) { // rhs = Δt
   // v{this} * Δt{rhs} -> Δp{Position}
   return toPosition(rhs);
}

Velocity & Velocity::operator = (const Velocity & rhs) {
   Vector::set(rhs.getX(), rhs.getY());
   return *this;
}

Velocity & Velocity::operator = (const Vector & rhs) {
   Vector::set(rhs);
   return *this;
}

/**************************************************
 * VELOCITY ostream insertion
 **************************************************/
std::ostream & operator << (std::ostream & out, const Velocity & rhs) {
   out << "(" << rhs.getX() << "m/s , " << rhs.getY() << "m/s)";
   return out;
}
   
/**************************************************
 * VELOCITY istream extraction
 **************************************************/
std::istream & operator >> (std::istream & in, Velocity & rhs) {
   double x, y;
   in >> x >> y;
   rhs.set(x, y);
   return in;
}
