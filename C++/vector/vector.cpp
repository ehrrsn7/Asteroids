/**********************************************************************
 * Source File: Vector
 **********************************************************************/

#include "vector.h"

#include "physicsFormulas.h"

/**************************************************
 * Methods
 **************************************************/
Vector Vector::forward(double angleRadians) {
   return Vector(formulas::trigX(1.0, angleRadians), formulas::trigY(1.0, angleRadians));
}

void Vector::set(double x, double y) {
   setX(x);
   setY(y);
}

void Vector::add(double dx, double dy) {
   addX(dx);
   addY(dy);
}

void Vector::add(const Vector & v) {
   // v stands for ds/dt where s is the base vector
   add(v.getX(), v.getY());
}

void Vector::setPolar(double magnitude, double angleRadians) {
   Vector::set(formulas::trigX(magnitude, angleRadians), formulas::trigY(magnitude, angleRadians));
}

double Vector::getMagnitude() const {
   return Trig::mag(*this);
}

void Vector::setMagnitude(double magnitude, double angleRadians) {
   setPolar(magnitude, angleRadians);
}

void Vector::addMagnitude(double magnitude, double angleRadians) {
   add(magnitude * sin(angleRadians), magnitude * cos(angleRadians));
}

void Vector::addPolar(double magnitude, double angleRadians) {
   addMagnitude(magnitude, angleRadians);
}

/**************************************************
 * Member Operator Overloading
 **************************************************/
Vector Vector::operator + (const Vector& rhs) {
   Vector newS;
   newS.add(rhs.getX(), rhs.getY());
   return newS;
}

Vector& Vector::operator += (const Vector& rhs) {
   add(rhs.getX(), rhs.getY());
   return *this;
}

Vector & Vector::operator = (const Vector & rhs) {
   set(rhs.getX(), rhs.getY());
   return *this;
}

/**************************************************
 * Non-Member Operator Overloading
 **************************************************/
std::ostream & operator << (std::ostream & out, const Vector& rhs) {
   out << "(" << rhs.getX() << ", " << rhs.getY() << ")";
   return out;
}

std::istream & operator >> (std::istream & in, Vector& rhs) {
   double x, y;
   in >> x >> y;
   rhs.set(x, y);
   return in;
}
