
package Asteroids.Objects;

import java.awt.Point;
import java.awt.Graphics;
import java.awt.Color;
import java.lang.Math;

public class Laser extends FlyingObject {

    // constants
    public static final int LASER_FIRING_SPEED = 10;
    
    // constructor
    public Laser(Point pInit, Point vInit, double direction) {
        name = "Laser";
        System.out.println(name + " created.");
        
        r = 4;
        deathTimer = 140;
        wrap = true;
        point.setLocation(pInit);
        
        velocity.setLocation(
            vInit.x + LASER_FIRING_SPEED * Math.cos(Math.toRadians(-direction)),
            vInit.y + LASER_FIRING_SPEED * Math.sin(Math.toRadians(-direction))
        );
    }
    
    // methods
    public void paintComponent(Graphics graphics) {
        super.paintComponent(graphics);
        System.out.println(name + ".paintComponent()");
        graphics.setColor(Color.LIGHT_GRAY);
        graphics.drawOval(point.x, point.y, r, r);
    }
}
