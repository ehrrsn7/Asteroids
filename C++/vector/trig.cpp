#include "vector.h"
#include "physicsFormulas.h"

const double Trig::deg(double angleRadians) {
    return formulas::deg(angleRadians);
}

const double Trig::rad(double angleDegrees) {
   return formulas::rad(angleDegrees);
}

const double Trig::mag(double x, double y) {
   return formulas::mag(x, y);
}

const double Trig::getMagnitude(double x, double y) {
   return formulas::mag(x, y);
}

const double Trig::mag(const Vector & s) {
   return formulas::mag(s);
}

const double Trig::getMagnitude(const Vector & s) {
   return formulas::mag(s);
}
