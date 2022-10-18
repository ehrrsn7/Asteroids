package com.example.asteroidsKotlin

import android.content.Context
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import kotlin.random.Random

class Asteroid(context: Context) : FlyingObject() {

    companion object {
        val initAmount = 5
        val asteroidSpeed = 1f
    }

    // src=http://pixelartmaker.com/art/b02b88d8461a4fb
    var bitmap: Bitmap = BitmapFactory.decodeResource(
        context.resources,
        R.drawable.asteroid)

    init {
        // attributes
        name = "asteroid"
        radius  = 200
        wrap = true

        // set up random position/launch in random direction
        point = Game.getRandomPointOnScreen()
        rotation = 360f * Random.nextFloat()
        launch(asteroidSpeed)

        // resize image
        bitmap = resizeBitmap(bitmap, radius)
    }
}