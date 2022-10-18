package com.example.asteroidsKotlin

import android.graphics.Point
import android.media.Image
import com.example.asteroidsKotlin.FlyingObject

class Laser : FlyingObject {
    constructor(
        point       : Point,
        velocity    : Velocity,
        rotation    : Float,
        laserSpeed  : Float = 5f)
    {
        // define FlyingObject attributes
        name        = "Laser"
        wrap        = true
        radius      = 10

        // launch
        this.point = Point(point.x, point.y)
        this.rotation = rotation
        launch(velocity.amount() + laserSpeed)
        deathTimer  = 40f
    }
}