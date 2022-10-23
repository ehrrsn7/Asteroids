import Projectile from "../scripts/misc scripts/projectile.js"
import draw from "../scripts/draw.js"
import Point from "../scripts/misc scripts/point.js";
import math from "../scripts/misc scripts/math.js";
import debug from "../scripts/misc scripts/debug.js";
import Velocity from "../scripts/misc scripts/velocity.js";
import Time from "../scripts/misc scripts/time.js";
import FPS from "../scripts/main.js";
const canvas = document.querySelector("canvas")
const context = canvas.getContext("2d")

const ROCK_SHIP_BUFFER = canvas.height - 50
const ROCK_SPEED = 5 // rock average speed in pixels / msecond

class Rock extends Projectile {
    constructor(p = -1, v = -1, id = 1) {
        super()
        this.name = "unknown asteroid"
        this.id = id
        this.a = math.randomrange(0, math.rad(360))
        this.dr = math.randomrange(-1, 1)
        this.nameRock()
        this.p_init(p)
        this.v_init(v)
        this.r_init()
        this.vertices = this.populate_vertecies()
    }

    p_init(p) {
        if (p == -1) {
            do {
                this.p = new Point(
                    math.randomrange(0, canvas.width),
                    math.randomrange(0, canvas.height)
                )
                var center_p = new Point(canvas.width / 2, canvas.height / 2)
            } while (math.dist(this.p, center_p) < canvas.width /  3)
        } else this.p = new Point(p.x, p.y)
    }

    v_init(v) {
        if (v == -1) {
            this.v = new Velocity(
                10 * ROCK_SPEED * math.randomrange(-1, 1) * FPS,
                10 * ROCK_SPEED * math.randomrange(-1, 1) * FPS
            )
        } else {
            this.v = new Velocity(
                v.dx + 10 * ROCK_SPEED * math.randomrange(-1, 1) * FPS,
                v.dy + 10 * ROCK_SPEED * math.randomrange(-1, 1) * FPS
            )
        }
    }

    r_init() {
        switch (this.id) {
            case 1:
                this.r = math.randomrange(30, 50)
                break
            case 2:
                this.r = math.randomrange(20, 30)
                break
            case 3:
                this.r = math.randomrange(10, 20)
                break
        }
    }

    populate_vertecies() {
        var vertices = []

        var offs = this.r
        var jag = .3
        for (var a = 0; a < 360; a += 45) {
            offs = this.r * math.randomrange(1 - jag, 1 + jag)
            vertices.push({ angle: a, offset: offs })
        }
        console.log(vertices)


        return vertices
    }

    nameRock() {
        switch (this.id) {
            case 1:
                this.name = "big rock"
                break
            case 2:
                this.name = "medium rock"
                break
            case 3:
                this.name = "small rock"
                break
        }
    }

    advance() {
        super.advance()
        if (this.timer < 0) this.alive = false
        this.a += this.dr
    }

    display() {
        super.display()
        draw.rock(
            this.p.x,
            this.p.y,
            this.r,
            this.a,
            this.vertices
        )
        if (this.timer != 0) this.drawExplosion()
    }

    hit() {
        if (this.timer == 0) this.explode()
    }

    explode() {
        this.timer = 1
    }

    drawExplosion() {
        if (this.timer < .4) draw.circle(this.p, this.r * 1.2, true, "yellow")
        if (this.timer < .7) draw.circle(this.p, this.r, true, "orange")
        if (this.timer < 1) draw.circle(this.p, this.r * 0.8, true, "red")
    }

    split() {
        return [
            new Rock(this.p, this.v, this.id + 1),
            new Rock(this.p, this.v, this.id + 1)
        ]
    }

    get points() {
        switch (this.id) {
            case 1:
                // big rock
                return 10
            case 2:
                // medium rock
                return 50
            case 3:
                // small rock
                return 100
        }
    }
}

export default Rock