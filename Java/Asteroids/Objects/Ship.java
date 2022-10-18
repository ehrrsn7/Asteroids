package Asteroids.Objects;

import java.awt.Color;
import java.awt.Graphics;
import java.lang.Math;

import Asteroids.Game.Asteroids;

public class Ship extends FlyingObject {

    private static final long serialVersionUID = 1L;

    // constants
    public static final int SHIP_ACCELERATE_AMOUNT = 3;


    // attributes
    public boolean upKeyHeld            = false;
    public boolean leftKeyHeld          = false;
    public boolean rightKeyHeld         = false;
    public static int whichDrawMethod   = 2;

    // constructor
    public Ship() {
        name        = "Ship";
        r           = 50;
        wrap        = true;
        point.setLocation(Asteroids.getScreenCenter());
    }

    public double ax = 0;
    // methods
    @Override
    public void paintComponent(Graphics graphics) {
        super.paintComponent(graphics);
        if (debug) System.out.println(name + ".paintComponent() [child]");

        graphics.setColor(Color.WHITE);
        graphics.drawOval(point.x - r/2, point.y - r/2, r, r);
        graphics.setColor(Color.white);
        graphics.drawOval(
            (int)(point.x + r * Math.cos(Math.toRadians(-rotation)) / 2),
            (int)(point.y + r * Math.sin(Math.toRadians(-rotation)) / 2),
            2, 2
        );

        switch (whichDrawMethod) {
            case 0:
                graphics.setColor(Color.WHITE);
                graphics.drawOval(point.x - r/2, point.y - r/2, r, r);
                graphics.setColor(Color.white);
                graphics.drawOval(
                    (int)(point.x + r * Math.cos(Math.toRadians(-rotation)) / 2),
                    (int)(point.y + r * Math.sin(Math.toRadians(-rotation)) / 2),
                    2, 2
                );
                break;
            case 1:
                graphics.setColor(Color.GREEN);
                shape.addPoint(point.x, point.y);
                shape.addPoint(point.x + 20, point.y);
                shape.addPoint(point.x + 20, point.y + 20);
                shape.addPoint(point.x, point.y + 20);
                graphics.drawPolygon(shape);
                break;
            case 2:
                graphics.setColor(Color.LIGHT_GRAY);
                graphics.drawLine(
                    point.x, point.y,
                    point.x - r/2, point.y + r/2
                );
                graphics.setColor(Color.GREEN);
                graphics.drawLine(
                    point.x - r/2, point.y + r/2, 
                    point.x, point.y - r
                );
                graphics.setColor(Color.RED);
                graphics.drawLine(
                    point.x, point.y - r, 
                    point.x + r/2, point.y + r/2
                );
                graphics.setColor(Color.BLUE);
                graphics.drawLine(
                    point.x + r/2, point.y + r/2,
                    point.x, point.y
                );
                break;
            default:
                break;
        }
    }

    @Override
    public void update() {
        super.update();
        handleEvents();
    }

    private void handleEvents() {
        if (upKeyHeld)      accelerate();
        if (leftKeyHeld)    addRotation(10);
        if (rightKeyHeld)   addRotation(-10);
    }

    public Laser fire() {
        System.out.print(name + ".fire() ");
        return new Laser(point, velocity, rotation);
    }

    public void accelerate() {
        super.accelerate(SHIP_ACCELERATE_AMOUNT);
    }

    public static void switchDrawFormat() {
        if (whichDrawMethod == 0) {
            whichDrawMethod = 1;
            return;
        }
        if (whichDrawMethod == 1) {
            whichDrawMethod = 2;
            return;
        }
        if (whichDrawMethod == 2) {
            whichDrawMethod = 0;
            return;
        }
    }
}
