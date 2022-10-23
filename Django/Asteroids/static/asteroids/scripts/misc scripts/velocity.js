import debug from "./debug.js"
import math from "./math.js"

class Velocity {
    constructor(dx = 0, dy = 0) {
        this.dx = dx,
            this.dy = dy
    }

    add(dv) {
        this.dx += dv.dx
        this.dy += dv.dy
    }

    forward(angle, magnitude = 1) {
        debug.display(`${magnitude}`, "angle")
        if (isNaN(angle)) angle = Math.atan2(this.dx, this.dy)
        angle += math.rad(90)
        return new Velocity(
            magnitude * Math.cos(angle),
            magnitude * Math.sin(angle)
        )
    }

    get speed() { return math.mag(this.dx, this.dy) }
    set speed(magnitude) {
        var angle = Math.atan2(this.dx, this.dy)
        this.dx = magnitude * Math.cos(angle)
        this.dy = magnitude * Math.sin(angle)
    }

    tostring() { return `(${this.dx}, ${this.dy})` }
}

export default Velocity