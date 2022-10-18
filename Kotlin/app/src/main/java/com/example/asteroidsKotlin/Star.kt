package com.example.asteroidsKotlin

import android.content.Context
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import androidx.appcompat.widget.AppCompatImageView
import kotlin.random.Random

class Star(context: Context) {

    companion object {
        val avgStarAmount   = 20
        val randOffset      = 10
    }

    val point = Game.getRandomPointOnScreen()
    val starSize = Random.nextInt(5, 25)



    init {
    }

    private fun createBitmap(context: Context, drawable:Int) =
            BitmapFactory.decodeResource(context.resources, drawable)
    private fun resizeBitmap(bitmap: Bitmap, radius: Int) =
            Bitmap.createScaledBitmap(bitmap, radius, radius, false)
}