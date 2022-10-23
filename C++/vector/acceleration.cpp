/**********************************************************************
 * acceleration.cpp
 * orbitSimulator
 **********************************************************************/

#include "vector.h"

#include "physicsFormulas.h"

/**************************************************
 * Methods
 **************************************************/
Acceleration Acceleration::forward(double angleRadians) {
   return Acceleration(formulas::trigX(1.0, angleRadians), formulas::trigY(1.0, angleRadians));
}

void Acceleration::add(const Acceleration & da) {
   Vector::add(da.getX(), da.getY());
}

Acceleration Acceleration::operator + (const Acceleration & rhs) { // rhs : Δt
   Acceleration newA = *this;
   newA.add(rhs);
   return newA;
}

Acceleration & Acceleration::operator += (const Acceleration & rhs) { // rhs : Δt
   add(rhs);
   return *this;
}

Velocity Acceleration::toVelocity(const double dt) {
   return Velocity(getX() * dt, getY() * dt);
}

Velocity Acceleration::operator * (const double rhs) { // rhs = Δt
   // v{this} * Δt{rhs} -> Δp{Posiiton}
   return toVelocity(rhs);
}

Acceleration & Acceleration::operator = (const Acceleration & rhs) {
   Vector::set(rhs.getX(), rhs.getY());
   return *this;
}

Acceleration & Acceleration::operator = (const Vector & rhs) {
   Vector::set(rhs);
   return *this;
}

/**************************************************
 * ACCELERATION ostream insertion
 **************************************************/
std::ostream& operator << (std::ostream& out, const Acceleration& rhs) {
   out << "(" << rhs.getX() << "m/s/s , " << rhs.getY() << "m/s/s)";
   return out;
}
   
/**************************************************
 * ACCELERATION istream extraction
 **************************************************/
std::istream& operator >> (std::istream& in, Acceleration& rhs) {
   double x, y;
   in >> x >> y;
   rhs.set(x, y);
   return in;
}
