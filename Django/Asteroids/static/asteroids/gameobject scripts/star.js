// import
import draw from "../scripts/draw.js"
import FPS from "../scripts/main.js"
import Projectile from "../scripts/misc scripts/projectile.js"
import debug from "../scripts/misc scripts/debug.js"
import time from "../scripts/misc scripts/time.js"
import Image from "../scripts/misc scripts/image.js"
import Point from "../scripts/misc scripts/point.js"
import Dimensions from "../scripts/misc scripts/dimensions.js"
import Laser from "./laser.js"
import Velocity from "../scripts/misc scripts/velocity.js"
import math from "../scripts/misc scripts/math.js"

const STAR_SIZE_AVG = .7 // pixels
const STAR_SPEED = 50 // px/s


class Star extends Projectile {
    constructor(screenWidth, screenHeight) {
        super()
        this.setRandomScreenPosition(screenWidth, screenHeight)
        this.screenHeight = screenHeight
        this.r = Math.random() * .7
        this.wrap = true
        this.velocity = new Velocity(
            0,
            STAR_SPEED
        )
    }

    setRandomScreenPosition(screenWidth, screenHeight) {
        this.p.set(
            Math.random() * screenWidth,
            Math.random() * screenHeight
        )
    }

    update() {
        this.p.y += Math.random() * STAR_SPEED * time.deltaTime
        this.draw()
        if (this.p.y > this.screenHeight) this.p.y = 0
    }

    draw() {
        draw.star(this.p, this.r)
    }
}

export default Star