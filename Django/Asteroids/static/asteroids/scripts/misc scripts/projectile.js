import FPS from "../main.js"
import debug from "./debug.js"
import GameObject from "./gameObject.js"
import Time from "./time.js"
import Velocity from "./velocity.js"

const ROTATION_AMOUNT = 7

class Projectile extends GameObject {
    constructor() {
        super()
        this.name = "unknown Projectile object"
        this.v = new Velocity(0, 0)
        this.rotation = 0
        this.friction = true
    }

    // properties
    get velocity() { return this.v }
    set velocity(new_v) { this.v = new_v }

    // methods
    update() {
        super.update()
        this.point.translate(this.velocity)
    }

    rotate(dr) { this.rotation -= dr * Time.deltaTime }
    rotateRight() { this.rotate(ROTATION_AMOUNT) }
    rotateLeft() { this.rotate(-ROTATION_AMOUNT) }

    accelerate(angle, amount) {
        this.velocity.add(this.velocity.forward(angle, amount))
    }

    applyFriction(amount) {
        if (this.friction) {
            if (this.velocity.speed > .1) {
                this.velocity.dx -= amount * this.velocity.dx
                this.velocity.dy -= amount * this.velocity.dy
            } else this.velocity.speed = 0
        }
    }
}

export default Projectile