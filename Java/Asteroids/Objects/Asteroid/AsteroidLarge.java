
package Asteroids.Objects.Asteroid;

import java.awt.Graphics;
import java.awt.Color;

public class AsteroidLarge extends Asteroid {

    // constants
    public static final int ASTEROID_LARGE_SPEED = 15;

    // constructor
    public AsteroidLarge() {
        asteroidCount++;
        name = "LargeAsteroid" + asteroidCount;
        System.out.println(name + " created.");
        r = 40;
        velocity.setLocation(
            ASTEROID_LARGE_SPEED * Math.cos(Math.toRadians(direction)),
            ASTEROID_LARGE_SPEED * Math.sin(Math.toRadians(direction))
        );
    }

    // methods
    @Override
    public void paintComponent(Graphics graphics) {
        super.paintComponent(graphics);
        if (debug) System.out.println(name + ".paintComponent() [child]\n");
        graphics.setColor(Color.GRAY);
        graphics.drawOval(point.x, point.y, r, r);
    }
}
