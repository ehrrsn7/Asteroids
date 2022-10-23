package com.example.asteroidsKotlin

import android.content.Context
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.graphics.Matrix
import android.graphics.Point
import kotlin.math.cos
import kotlin.math.pow
import kotlin.math.sin
import kotlin.math.sqrt

abstract class FlyingObject {

    var name    = "Unknown Flying Object"

    var point                   : Point     = Point(0,0)
    protected var velocity      : Velocity  = Velocity()

    var radius        : Int       = 0
    protected var rotation      : Float     = 90f
    protected var deathTimer    : Float     = 0f

    var alive                   : Boolean   = true
    protected var wrap          : Boolean   = false
    protected var debug         : Boolean   = false


    /** public methods **/

    // update
    public open fun update(dt: Long) {
        if (!alive) return

        // debug
        if (debug) print("$name.update() ")

        // translate
        point.translate(velocity.dx, -velocity.dy)
        if (debug) println("$point ")

        // wrap edges
        wrap()

        // handle death timer
        if (deathTimer > 0)
            deathTimer -= dt.toFloat() / Game.fps.toFloat()
        else if (deathTimer < 0)
            alive = false

        if (debug) print("$deathTimer $dt")

        // handle rotation 'overlap'
        while (rotation < 0)    rotation += 360f
        while (rotation >= 360) rotation -= 360f
        if (debug) print("$rotation ")
    }

    /** event helper methods **/

    // accelerate
    fun accelerate(amount: Float) {
        if (debug) print("$name.accelerate($velocity) ")
        velocity.translate(
            (amount * cos(Math.toRadians(rotation.toDouble()))).toFloat(),
            (amount * sin(Math.toRadians(rotation.toDouble()))).toFloat()
        )
    }

    // launch (alt accelerate)
    fun launch(amount: Float) { accelerate(10 * amount) }

    // rotate
    fun rotate(amount: Float) { rotation += amount }

    // handle collisions
    fun handleCollision(obj: FlyingObject) {
        if (!debug) println("$name.handleCollision(${obj.name})")
        var distance = dist(this, obj)
        var tooClose = radius * 2 + obj.radius * 2
        var hit = distance < tooClose
         if (hit) {
            if (!debug)
                print("$name detected collision from ${obj.name} ")
            alive       = false
            obj.alive   = false
        }
    }

    private fun dist(obj1: FlyingObject, obj2: FlyingObject) : Int {
        return sqrt(
            obj1.point.x.toDouble().pow(2) +
            obj2.point.x.toDouble().pow(2)
        ).toInt()
    }


    /** wrap (private) **/

    protected var screen = Game.screenDimensions

    private fun wrap() {

        // quick exit
        if (!wrap) return

        // debug
        if (debug) print("$name.wrap() ")

        // right -> left
        if (point.x > screen.right)
            point.x = screen.left - radius

        // left -> right
        else if (point.x < screen.left - radius)
            point.x = screen.right

        // bottom -> top
        if (point.y > screen.bottom)
            point.y = screen.top - radius

        // top -> bottom
        else if (point.y < screen.top - radius)
            point.y = screen.bottom
    }

    /** bitmap helper functions **/
    protected fun createBitmap(context: Context, drawable:Int) =
        BitmapFactory.decodeResource(context.resources, drawable)
    protected fun resizeBitmap(bitmap: Bitmap, size: Int) =
        Bitmap.createScaledBitmap(bitmap, size, size, false)
}

// I really like having this 'adder'
private fun Point.translate(x: Float, y: Float) {
    this.x += x.toInt()
    this.y += y.toInt()
}

// add operator for rotating bitmap 'images'
fun Bitmap.rotate(degrees: Float): Bitmap {
    print("bitmap.rotate($degrees)")
    return Bitmap.createBitmap(this,
            0, 0, width, height,
            Matrix().apply { postRotate(degrees) },
            true)
    // src: https://gist.github.com/codeswimmer/858833
}

// very brief velocity class definition
class Velocity(var dx: Float = 0f, var dy: Float = 0f) {
    public fun translate(ddx:Float, ddy:Float)
        { dx += ddx; dy += ddy }

    public fun amount() : Float {
        return sqrt(dx.toDouble().pow(2) + dy.toDouble().pow(2))
            .toFloat()
    }
}
