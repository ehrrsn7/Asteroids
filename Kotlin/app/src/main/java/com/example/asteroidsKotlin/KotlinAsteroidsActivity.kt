package com.example.asteroidsKotlin

import android.annotation.SuppressLint
import android.app.Activity
import android.graphics.Point
import android.os.Build
import android.os.Bundle
import android.view.MotionEvent
import android.view.View
import android.widget.Button
import androidx.annotation.RequiresApi

class KotlinAsteroidsActivity : Activity(), View.OnTouchListener {

    /** objects/helper functions to be referenced in other
     * files in package **/
    companion object {
        var screenDimensions = Point() // populate in onCreate()
    }

    /** 'main' **/
    @SuppressLint("ClickableViewAccessibility")
    @RequiresApi(Build.VERSION_CODES.R)
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        // load the resolution into a dimensions object
        this.display?.getRealSize(screenDimensions)
        if (display == null)
            println("Unable to Load screen dimensions($screenDimensions)")
        else println("Screen Dimensions: $screenDimensions")

        // finish setup
        println("Asteroids App compiled")
        setContentView(R.layout.activity_kotlin_asteroids)

        // set up touch event listeners
        findViewById<Button>(R.id.shipAccelerateButton).setOnTouchListener(this)
        findViewById<Button>(R.id.shipFireLaserButton).setOnTouchListener(this)
        findViewById<Button>(R.id.shipRotateLeftButton).setOnTouchListener(this)
        findViewById<Button>(R.id.shipRotateRightButton).setOnTouchListener(this)
    }

    override fun onTouch(v: View?, event: MotionEvent?): Boolean {
        when (event?.action) {
            MotionEvent.ACTION_DOWN -> {
                when (v?.id) {
                    R.id.shipAccelerateButton   -> Game.heldKeys.thrust         = true
                    R.id.shipFireLaserButton    -> Game.heldKeys.fireLaser      = true
                    R.id.shipRotateLeftButton   -> Game.heldKeys.rotateLeft     = true
                    R.id.shipRotateRightButton  -> Game.heldKeys.rotateRight    = true
                }
                return true
            }

            MotionEvent.ACTION_UP -> {
                when (v?.id) {
                    R.id.shipAccelerateButton   -> Game.heldKeys.thrust         = false
                    R.id.shipFireLaserButton    -> Game.heldKeys.fireLaser      = false
                    R.id.shipRotateLeftButton   -> Game.heldKeys.rotateLeft     = false
                    R.id.shipRotateRightButton  -> Game.heldKeys.rotateRight    = false
                }
                return true
            }
        }

        return false
    }

    override fun onResume() {
        super.onResume()
    }

    override fun onPause() {
        super.onPause()
    }
}