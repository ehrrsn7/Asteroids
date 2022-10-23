package com.example.asteroidsKotlin

import android.content.Context
import android.graphics.*
import android.util.AttributeSet
import android.view.SurfaceView
import kotlin.random.Random

class Game (context: Context, attributeSet: AttributeSet)
    : SurfaceView(context, attributeSet), Runnable {

    // companion object (static attributes)
    companion object {
        val screenDimensions = Rect(
                0, 0,
                KotlinAsteroidsActivity.screenDimensions.x,
                KotlinAsteroidsActivity.screenDimensions.y
        )

        fun getRandomPointOnScreen() = Point(
                Random.nextInt(
                        screenDimensions.left,
                        screenDimensions.right),
                Random.nextInt(
                        screenDimensions.top,
                        screenDimensions.bottom)
        )

        fun getCenterPoint() = Point(
                screenDimensions.centerX(),
                screenDimensions.centerY()
        )

        var heldKeys = HeldKeys()
        val fps : Long = 60
    }

    // game-related attributes
    private var debug : Boolean = false

    // game objects
    private var ship        = Ship(context)
    private val lasers      = arrayListOf<Laser>()
    private val asteroids   = arrayListOf<Asteroid>()
    private val stars       = arrayListOf<Star>()

    // held keys
    data class HeldKeys (
        var thrust      : Boolean = false,
        var rotateLeft  : Boolean = false,
        var rotateRight : Boolean = false,
        var fireLaser   : Boolean = false
    )

    /** constructor **/
    init {
        // asteroid belt
        for (i in 1..Asteroid.initAmount)
            asteroids.add(Asteroid(context))

        // stars
        for (i in 1..Random.nextInt(
                Star.avgStarAmount - Star.randOffset,
                Star.avgStarAmount + Star.randOffset
        )) stars.add(Star(context))
    }

    /** start **/
    override fun onLayout(
            changed: Boolean,
            left: Int, top: Int,
            right: Int, bottom: Int) {

        super.onLayout(changed, left, top, right, bottom)

        thread.start()
    }

    /** tick/update **/
    private val thread  : Thread    = Thread(this) // begin loop
    private var before  : Long      = System.currentTimeMillis()
    private var now     : Long      = System.currentTimeMillis()
    private var dt      : Long      = now - before

    override fun run() {
        now     = System.currentTimeMillis()
        dt      = now - before
        before  = now
        while (true) {
            update()
            Thread.sleep(1000/fps)
            if (debug) print("Thread.sleep(1000/fps)")
        }
    }

    private fun update() {
        if (debug) println("running...")

        draw()
        handleEvents()

        ship.update(dt)
        for (rock in asteroids) rock.update(dt)
        for (laser in lasers) laser.update(dt)
    }


    /** render/draw **/                     //(context - WHERE to draw)
    private var canvas = Canvas()           // canvas - WHAT to draw
    private val paint = Paint().apply {     // paint - HOW to draw
        color = Color.BLACK }

    private fun draw() {
        if (holder.surface.isValid) {
            if (debug) print("game.draw() // ")

            // Lock the canvas ready to draw
            canvas = holder.lockCanvas()

            // Draw the background color
            canvas.drawColor(Color.BLACK)


            /**
            // stars
            for (star in stars) {
                star.incrementFrame()
                canvas.drawBitmap(star.frames[star.frame],
                        star.point.x.toFloat(),
                        star.point.y.toFloat(),
                        paint
                )
            }
             **/

            /** Draw all the game objects here **/
            // Now draw the player spaceship
            canvas.drawBitmap(
                    ship.getFrame(),
                    ship.point.x.toFloat() - ship.radius/2,
                    ship.point.y.toFloat() - ship.radius/2,
                    paint
            )

            // asteroids
            for (rock in asteroids)
                canvas.drawBitmap(
                        rock.bitmap,
                        rock.point.x.toFloat() - rock.radius/2,
                        rock.point.y.toFloat() - rock.radius/2,
                        paint
                )

            paint.color = Color.RED
            for (laser in lasers)
                canvas.drawCircle(
                    laser.point.x.toFloat() - laser.radius/2,
                    laser.point.y.toFloat() - laser.radius/2,
                    laser.radius.toFloat(),
                    paint
                )

            // Draw everything to the screen
            holder.unlockCanvasAndPost(canvas)
        }
    }

    /** handle events **/
    private fun handleEvents() {
        // handle ship events (button listener keys)
        ship.handleEvents()
        if (heldKeys.fireLaser) lasers.add(ship.fire())

        // handle collisions/dead objects
        for (rock in asteroids) {
            ship.handleCollision(rock)

            for (laser in lasers)
                laser.handleCollision(rock)
        }

        cleanUpZombies()
    }

    private fun cleanUpZombies() {
        for (laser in lasers)
            if (!laser.alive) {
                lasers.remove(laser)
                break
            }

        for (rock in asteroids)
            if (!rock.alive) {
                asteroids.remove(rock)
                break
            }

        // TODO: if ship is dead, handle game state
    }
}
