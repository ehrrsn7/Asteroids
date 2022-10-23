// import
import Point from "./point.js"
import Dimensions from "./dimensions.js"
import Time from "./time.js"
import draw from "../draw.js"
import debug from "./debug.js"

/************
 * @abstract
 ************/
class GameObject {
    constructor(x = 0, y = 0, w = 0, h = 0, r = 0, a = 0) {
        this.name = "unknown GameObject"
        this.p = new Point(x, y)
        this.dim = new Dimensions(w, h)
        this.r = r // radius
        this.a = a // angle (radians)
        this.alive = true
        this.timer = 0 // death timer
    }

    // update (advance)
    update() {
        this.display()
        this.handleInput()
        this.handleTimer()
    }

    // display (draw)
    display() {
        this.showBounding()
            // debug.log(this.name + ".display() called")
    }

    boundingColor = "green"
    showBounding() {
        if (draw.showBounding) {
            if (this.alive)
                draw.circle(this.p, this.r, false, "green")
            else
                draw.circle(this.p, this.r, true, "red")
        }
    }

    // handle input
    handleInput() {

    }

    // handle death timer
    handleTimer() {
        if (this.timer > 0) this.timer -= Time.deltaTime
        else if (this.timer < 0) {
            this.alive = false
            console.log(`${this.name}.alive = false`)
        }
        // note that these statements don't specifically handle the case where this.timer == 0.
        // this is by design: essentially, the 'self-destruct' sequence is initiated by setting this.timer != 0.
    }

    hit() {
        this.alive = false
    }

    // fixed update? also implement tick/render if so

    // properties (getters/setters)
    get point() { return this.p }
    set point(new_p) { this.p = new_p }

    get radius() { return this.r }
    set radius(new_r) { this.r = new_r }

    get angleRadians() { return this.a }
    set angleRadians(new_a) { this.a = new_a }

    get dimensions() { return this.dim }
    set dimensions(new_dim) { this.dim = new_dim }
}

export default GameObject