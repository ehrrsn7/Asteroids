package com.example.asteroidsKotlin

import android.content.Context
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.widget.Button
import kotlin.random.Random

class Ship(context: Context) : FlyingObject() {

    /** basic content **/
    val shipSpeed = 2f
    val shipRotateSpeed = 5f

    init {
        name = "Ship"
        wrap = true
        radius = 200
        rotation = 90f
        point = Game.getCenterPoint()
    }

    /** bitmap frames **/
    // src=https://www.clipartkey.com/view/iRhiwi_8-bit-spaceship-png-8-bit-spaceship-sprites/
    val frames = arrayListOf<Bitmap>()

    init {
        frames.add(createBitmap(context, R.drawable.ship_1))
        frames.add(createBitmap(context, R.drawable.ship_2))
        frames.add(createBitmap(context, R.drawable.ship_3))
        frames.add(createBitmap(context, R.drawable.ship_4))
        frames.add(createBitmap(context, R.drawable.ship_5))
        frames.add(createBitmap(context, R.drawable.ship_6))
        frames.add(createBitmap(context, R.drawable.ship_7))
        frames.add(createBitmap(context, R.drawable.ship_8))
        frames.add(createBitmap(context, R.drawable.ship_9))
        frames.add(createBitmap(context, R.drawable.ship_10))
        frames.add(createBitmap(context, R.drawable.ship_11))
        frames.add(createBitmap(context, R.drawable.ship_12))

        for (i in 0..11) frames[i] = resizeBitmap(frames[i], radius)
    }

    fun handleEvents() {
        if (Game.heldKeys.thrust) accelerate(shipSpeed)
        if (Game.heldKeys.rotateLeft)   rotate( shipRotateSpeed)
        if (Game.heldKeys.rotateRight)  rotate(-shipRotateSpeed)
    }

    fun fire() : Laser { return Laser(point, velocity, rotation) }

    fun getFrame(): Bitmap {
        for (i in 0..11) {
            if (rotation >= 360 || rotation < 0 || frames.size >= 12) break
            return frames[(rotation / i).toInt()]
        }
        return frames[0] // default: up
    }
}