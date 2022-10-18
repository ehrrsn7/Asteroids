/**********************************
 * ASTEROIDS
 * driver file: includes main()
 * used example by leonardo-ono:
 * https://github.com/leonardo-ono/Java2DAsteroidsSurvival
 * (note that our code is very different, I mainly just used his for reference)
 **********************************/

package Asteroids;

import Asteroids.Game.*;

// class definition
public class Driver {

    /** Static Constants **/
    public static final int screenWidthInit = 800;
    public static final int screenHeightInit = 500;

    /** attributes **/
    private Asteroids game;

    /** main **/
    public static void main(String[] args) {
        Driver driver = new Driver();
        driver.setUpGame();
        driver.gameLoop();
    }

    /** non-static methods **/
    private void setUpGame() {
        System.out.println("Setting up Game.");
        game = new Asteroids();
    }

    private void gameLoop() {
        System.out.println("Setting up " + game.name + " game loop.");
        while (isRunning) tick();
        System.out.println("Exiting game loop.");
    }
 
    /** TICK **/
    public static boolean isRunning     = true;
    public static long    before        = System.nanoTime();
    public static long    now           = System.nanoTime();
    public static double  amountOfTicks = 60;
    public static double  ns            = 1000000000/amountOfTicks;
    public static double  delta         = 0;
    public static long    timer         = System.currentTimeMillis();
    public static int     frames        = 0;

    private void tick() {
        // code from https://gamedev.stackexchange.com/questions/52841/the-most-efficient-and-accurate-game-loop

        now = System.nanoTime();
        delta += (now - before) / ns;
        before = now;

        while(delta >= 1) {
            game.update();
            delta--;
        }
        frames++;

        if (System.currentTimeMillis() - timer > 1000) {
            timer += 1000;
            frames = 0;
        }
        before = System.nanoTime();
    }
}
