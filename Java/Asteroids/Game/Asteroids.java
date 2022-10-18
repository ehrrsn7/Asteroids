/**
 * Asteroids Game file
 *
 * This Game object houses all of the Game objects and methods.
 * Primary Methods:
 * - update()
 * Methods called by update():
 * - paint() [invoked by repaint() in update()]
 */

package Asteroids.Game;

import java.awt.Point;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.BorderLayout;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;

import javax.swing.JFrame;
import javax.swing.JPanel;

import java.util.List;
import java.util.ArrayList;

import Asteroids.Driver;
import Asteroids.Objects.*;
import Asteroids.Objects.Asteroid.*;

public class Asteroids extends JFrame {

    // constants
    private static final long serialVersionUID = 1L;

    // attributes
    public String name = "Asteroids";
    public boolean debug = true;

    // screen Dimensions / key Points
    private static Dimension screenDimensions = new Dimension(
        Driver.screenWidthInit,
        Driver.screenHeightInit
    );

    public static Dimension getScreenDimensions() {
        return screenDimensions;
    }

    public static Point getScreenCenter() {
        return new Point(
            screenDimensions.width/2,
            screenDimensions.height/2
        );
    }

    // screen background
    private static JPanel myBackground  = new Background();

    // game objects
    private Ship            ship        = new Ship();
    private List<Asteroid>  asteroids   = new ArrayList<>();
    private List<Laser>     lasers      = new ArrayList<>();

    // constructor
    public Asteroids() {
        System.out.println(name + " (Game object) created.");

        // set up JFrame (window)
        System.out.println("Setting up " + name + " game window.");
        setTitle(name);
        setPreferredSize(screenDimensions);
        setSize(screenDimensions);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(true);
        setLocationRelativeTo(null);
        pack();
        setVisible(true);

        // set up Event Handling
		addComponentListener(new WindowSizeChangeListener());
		addKeyListener(new MyKeyListener());
		setFocusable(true);

        // initialize game objects
        FlyingObject.setScreenDimensions(screenDimensions);
        asteroidBelt(5);
    }

    // update / advance
    public void update() {
        if (debug){
            clearTerminalWindow();
            System.out.print(name + ".update() ");
            System.out.println(Driver.delta);
        }

        // update game objects
        ship.update();
        for (Asteroid asteroid : asteroids) asteroid.update();
        for (Laser laser : lasers) laser.update();

        // event handling
        handleCollisions();
        cleanUpZombies();

        // refresh screen
        repaint();
        revalidate();
    }

    // draw / display
    private Image dbImage;
    private Graphics dbGraphics;

    @Override
    public void paint(Graphics graphics) {
        if (debug) System.out.println(name + ".paint()");

        // draw background
        graphics.setColor(Background.backgroundColor);
        graphics.fillRect(0, 0, screenDimensions.width, screenDimensions.height);
        myBackground.paintComponents(graphics);

        // draw each game object
        for (Asteroid asteroid : asteroids) asteroid.paintComponent(graphics);
        for (Laser laser : lasers) laser.paintComponent(graphics);
        ship.paintComponent(graphics);
    }


    // private helper methods (sorted by order called)
    private void asteroidBelt(int amount) {
        // create 'amount' of asteroids to add to 'this.asteroids'
        for (int i = 0; i < amount; i++) {
            Asteroid newAsteroid = new AsteroidLarge();
            asteroids.add(newAsteroid);
            add(newAsteroid, BorderLayout.PAGE_START);
        }
    }

    private void clearTerminalWindow() {
        // debug: clear terminal window
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    // handle events

    // handle collisions
    private void handleCollisions() {

    }

    // remove dead game objects
    private void cleanUpZombies() {
        for (Laser laser : lasers) {
            if (!laser.alive) {
                lasers.remove(laser);
                break;
            }
        }

        for (Asteroid asteroid : asteroids) {
            if (!asteroid.alive) {
                asteroids.remove(asteroid);
                break;
            }
        }
    }

    // key events
    private class MyKeyListener implements KeyListener {
        // handle input

        @Override
		public void keyTyped(KeyEvent e) { }

		@Override
		public void keyPressed(KeyEvent e) {
            if (debug) System.out.println(
                "keyPressed="+KeyEvent.getKeyText(e.getKeyCode())
            );

            switch (e.getKeyCode()) {
                case KeyEvent.VK_UP:
                    ship.upKeyHeld = true;
                    break;

                case KeyEvent.VK_LEFT:
                    ship.leftKeyHeld = true;
                    break;

                case KeyEvent.VK_RIGHT:
                    ship.rightKeyHeld = true;
                    break;

                case 'Q':
                    // quit the game (break the game loop)
                    System.out.println("Asteroids.quit()");
                    Driver.isRunning = false;
                    break;

                case 'X':
                    asteroids.remove(0);
                    break;

                case 'A':
                    asteroids.add(new AsteroidLarge());
                    break;

                case 'L':
                    Ship.switchDrawFormat();
                    break;

                case ' ':
                    // fire laser
                    Laser newLaser = ship.fire();
                    lasers.add(newLaser);
                    add(newLaser);
                    break;

                default:
                    break;
            }
        }

		@Override
		public void keyReleased(KeyEvent e) {

            switch (e.getKeyCode()) {
                case KeyEvent.VK_UP:
                    ship.upKeyHeld = false;
                    break;

                case KeyEvent.VK_LEFT:
                    ship.leftKeyHeld = false;
                    break;

                case KeyEvent.VK_RIGHT:
                    ship.rightKeyHeld = false;
                    break;

                default:
                    break;
            }
        }
    }

    // window (jframe) resize event
    private class WindowSizeChangeListener implements ComponentListener {

        @Override
        public void componentMoved(ComponentEvent e) {
            // TODO Auto-generated method stub
            System.out.println("window moved");
        }

        @Override
        public void componentResized(ComponentEvent e) {
            // TODO Auto-generated method stub
            System.out.println("window resized");
            System.out.println(" - new 'size' == " + getSize().toString());
            System.out.println(" - new 'preferredSize' == " + getPreferredSize());
            screenDimensions.width = (int)(getSize().getWidth());
            screenDimensions.height = (int)(getSize().getHeight());
            FlyingObject.setScreenDimensions(screenDimensions);
        }

        @Override
        public void componentHidden(ComponentEvent e) {
            // TODO Auto-generated method stub
            System.out.println("window hidden");
        }

        @Override
        public void componentShown(ComponentEvent e) {
            // TODO Auto-generated method stub
            System.out.println("window shown");
        }
    }
}
