import debug from "./debug.js"
import FPS from "../main.js"
import Time from "./time.js"

class Point {
    constructor(x = 0, y = 0) {
        this.x = x
        this.y = y
    }

    translate(v) {
        this.x += v.dx * Time.deltaTime / FPS
        this.y -= v.dy * Time.deltaTime / FPS
    }

    set(x, y) {
        this.x = x
        this.y = y
    }

    get up() { return new Point(0, -1) }
    get down() { return new Point(0, 1) }
    get right() { return new Point(1, 0) }
    get left() { return new Point(-1, 0) }

    tostring() { return `Point: ${this.x} ${this.y}` }
}

export default Point