//
//  velocity.hpp
//  Asteroids
//
//  Created by Elijah Harrison on 11/7/20.
//

#ifndef velocity_hpp
#define velocity_hpp

#include <math.h>
#include <iostream>

class Trig {
public:
    static float rad(float angleDegrees) {
        // angle deg -> rad
        return angleDegrees * M_PI / 180;
    }

    static float deg(float angleRadians) {
        // angle rad -> deg
        return angleRadians * 180 / M_PI;
    }
    
    static float getMagnitude(float x, float y) {
        // (x, y) -> s̅
        return sqrt(x*x + y*y);
    }
    
    static float xyToAngleRadians(float x, float y) {
        // ø = tan(-¹)(y/x)
        return atan2(y, x);
    }
    
    static float momentumFromMassVelocity(float m, float vMag) {
        // ρ = m v
        return m * vMag;
    }
    
    static float velocityMagnitudeFromMassMomentum(float p, float m) {
        // ρ = m v
        // -> v = ρ / m
        return p / m;
    }
};

class Velocity {

private:
    float dx;
    float dy;

public:
    Velocity() {
        setDx(0.0);
        setDy(0.0);
    }

    Velocity(float dx, float dy) {
        setDx(dx);
        setDy(dy);
    }
    
    Velocity(const Velocity & rhs) {
        setDx(rhs.getDx());
        setDy(rhs.getDy());
    }
    
    // getters
    float getDx() const { return dx; }
    float getDy() const { return dy; }
    
    static Velocity forward(float angleRadians) {
        return Velocity(cos(angleRadians), sin(angleRadians));
    }
    
    // setters
    void setDx(float new_dx) { dx = new_dx; }
    void setDy(float new_dy) { dy = new_dy; }
    void set(Velocity new_v) {
        setDx(new_v.getDx());
        setDy(new_v.getDy());
        std::cout << "\tv set to: "; print(); std::cout << std::endl;
    }
    
    // alternate reference system: magnitude/angle
    void setMagnitudeAngle(float mag, float angleRadians) {
        setDx(mag * cosf(angleRadians));
        setDy(mag * sinf(angleRadians));
    }
    
    void setAngle(float angleRadians) {
        setMagnitudeAngle(Trig::getMagnitude(dx, dy), angleRadians);
    }
    
    float getAngle() const { return Trig::xyToAngleRadians(dx, dy); }
    
    // alternate calculation: momentum/mass -> velocity
    void setVMagFromMassMomentum(float p, float m) {
        float vMag = Trig::velocityMagnitudeFromMassMomentum(p, m);
        float oldAngle = getAngle();
        setMagnitudeAngle(vMag, oldAngle);
    }
    
    float getSpeed()        const { return Trig::getMagnitude(dx, dy); }
    float getAngleRadians() const { return atan2(dy, dx); }
    float getAngleDegrees() const { return Trig::deg(getAngleRadians()); }
    
    // apply force
    void applyForce(float F, float m, float angleRadians) {
        if (abs(m) <= 0.1) return; // quick exit to avoid /0 error
        std::cout << "Applying force on v obj \n";
        // F = m a
        Velocity dv;
        dv.setMagnitudeAngle(F / m, angleRadians);
        add(dv);
        std::cout << "final v after force : " << getSpeed() << std::endl;
    }
    
    // add/subtract
    void add(const Velocity & dv) {
        dx += dv.dx;
        dy += dv.dy;
    }
    
    void subtract(const Velocity & dv) {
        dx -= dv.dx;
        dy -= dv.dy;
    }
    
    // operators
    Velocity operator * (float rhs) {
        return Velocity(dx * rhs, dy * rhs);
    }
    
    Velocity operator / (float rhs) {
        return Velocity(dx / rhs, dy / rhs);
    }
    
    Velocity operator - (const Velocity rhs) {
        return Velocity(dx - rhs.dx, dy - rhs.dy);
    }
    Velocity operator - () {
        return Velocity(-dx, -dy);
    }
    
    Velocity operator + (const Velocity rhs) {
        return Velocity(dx + rhs.dx, dy + rhs.dy);
    }
    Velocity operator + () {
        return Velocity(+dx, +dy);
    }
    
    void print() const { std::cout << "(" << dx << ", " << dy << ")"; }
};

#endif /* velocity_hpp */
