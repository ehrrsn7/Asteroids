// import
import debug from "../scripts/misc scripts/debug.js"
import time from "../scripts/misc scripts/time.js"
import draw from "../scripts/draw.js"
import Image from "../scripts/misc scripts/image.js"
import Projectile from "../scripts/misc scripts/projectile.js"
import Point from "../scripts/misc scripts/point.js"
import Dimensions from "../scripts/misc scripts/dimensions.js"
import Laser from "./laser.js"
import Velocity from "../scripts/misc scripts/velocity.js"
import math from "../scripts/misc scripts/math.js"
import GameObject from "../scripts/misc scripts/gameObject.js"
import FPS from "../scripts/main.js"
const canvas = document.querySelector("canvas")

// define
const ACCELERATION_AMOUNT = 100 // ship acceleration amount in pixels/s/s
const FRICTION_AMOUNT = 0.1 // brake deceleration amount
const LASER_DELAY = .05 // cannon delay rate in frames

// ship module
class Ship extends Projectile {
    constructor() {
        console.log("Ship constructor called.")

        // set GameObject components
        super()
        this.name = "Ship"
        this.point = new Point(canvas.width / 2, canvas.height / 2)
        this.velocity = new Velocity(0, 0)
        this.r = 15
        this.dimensions = new Dimensions(1, 1)
        this.a = 10
        this.image = new Image("../assets/shipImage.png", "ship image", this.dim, true)
        this.laserDelayTimer = 0

        // set ship components
        this.brake = false
    }

    // methods
    update() {
        super.update()
        this.handleInvulnerability()
        this.handleLaserDelay()
        if (this.brake) {
            this.applyFriction(FRICTION_AMOUNT)
            debug.display("Braking...")
        }
    }

    display() {
        if (this.blinkOn) {
            super.display()
            if (!draw.drawImages)
                draw.triangle(this.point, this.r, this.rotation)
            if (this.timer > 0) this.drawExplosion()
        }
    }

    handleInput() {
        super.handleInput()
    }

    thrust() {
        this.accelerate(this.rotation, ACCELERATION_AMOUNT)
    }

    fire() {
        this.laserDelayTimer = LASER_DELAY + 1 // disable cannon for 'x' frames
        return new Laser(this.p.x, this.p.y, this.v.dx, this.v.dy, this.rotation, this.r)
    }

    hit() {
        if (this.timer == 0) this.explode()
    }

    explode() {
        this.timer = 1
    }

    drawExplosion() {
        if (this.timer < .4) draw.circle(this.p, this.r * 1.2, true, "yellow")
        if (this.timer < .6) draw.circle(this.p, this.r, true, "orange")
        if (this.timer < .8) draw.circle(this.p, this.r * 0.8, true, "red")
        draw.triangle(this.p, this.r - 2, this.rotation, "red", 1)
        draw.triangle(this.p, this.r - 7, this.rotation, "orange", 3)
        draw.triangle(this.p, this.r - 12, this.rotation, "yellow", 3)
        draw.triangle(this.p, 1, this.rotation, "red", 1)
    }

    get invulnerable() { return this.invulnerabilityTimer > 0 }
    invulnerabilityTimer = 2
    handleInvulnerability() {
        if (this.invulnerabilityTimer > 0)
            this.invulnerabilityTimer -= time.deltaTime
    }
    get blinkOn() {
        var rate = .5
        var y = this.invulnerabilityTimer - Math.floor(this.invulnerabilityTimer)
        if (y < rate) return false
        else if (y < rate * 2) return true
        else if (y > 0) y -= rate
        else return true
    }

    handleLaserDelay() {
        debug.display("handleLaserDelay()", "functionalLaserDelay()Msg")

        if (this.laserDelayTimer >= 0) {
            debug.display(`${this.laserDelayTimer-1}`, "laserDelayTimer")
            this.laserDelayTimer -= time.deltaTime
        }
        if (this.laserDelayTimer <= 1) this.laserDelayTimer = 0
    }
}

// export module
export default Ship