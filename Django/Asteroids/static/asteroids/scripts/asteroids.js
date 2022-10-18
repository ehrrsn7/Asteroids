import draw from "./draw.js"
import Ship from "../gameobject scripts/ship.js"
import Star from "../gameobject scripts/star.js"
import { loadShipLives } from "./stateManager.js"
import Rock from "../gameobject scripts/rock.js"
import debug from "./misc scripts/debug.js"
import time from "./misc scripts/time.js"
import collisionHandler from "./collisionHandler.js"
const canvas = document.querySelector("canvas")

// state 'enum'
const state_strings = [
    "RESUME",
    "PAUSE",
    "MAIN_MENU",
    "OPTIONS_MENU",
    "HIGH_SCORES_MENU",
    "QUIT"
]

const states = enumerator(state_strings)

function displayState(state) {
    var msg = `{${state} : ${state_strings[state]}}`
    debug.log(msg)
    return msg
}

function enumerator(list) {
    var key_value_pair_map = {}
    list.forEach((str_val, index) => {
        key_value_pair_map[str_val] = index
    })
    return key_value_pair_map
}


// Asteroids Game
class Game {
    constructor() {
        console.log("Game constructor called.")

        // game objects
        this.ship = new Ship()
        this.shipLives = loadShipLives(4) // [n shipLife's]
        this.lasers = []
        this.rocks = []
        this.stars = []
        for (let i = 0; i < 100; i++)
            this.stars.push(new Star(canvas.width, canvas.height))
        this.asteroidBelt(8)
        Game.state = states.RESUME

        // other
        this.score = 0
    }

    /**********
     * STATICS
     **********/
    static state = states.PAUSE
    static heldKeys = {}

    /*********
     * UPDATE
     *********/
    update() {
        draw.fillBackground()

        // TODO: display the score using html/js instead of canvas.context
        draw.drawText(this.score)
        document.getElementById("score").innerHTML = `${this.score}`

        // handle states
        debug.display(`${displayState(Game.state)}`, "gameState")
        switch (Game.state) {
            case states.RESUME:
                this.handleCollisions()
                this.stars.forEach((star) => star.update())
                this.rocks.forEach((rock) => rock.update())
                this.lasers.forEach((laser) => laser.update())
                for (var i in this.shipLives) this.shipLives[i].update()
                this.ship.update()

                break;

            case states.PAUSE:
                displayState(Game.state)
                break;

            default:
                break;
        }

        if (this.rocks.length <= 0) this.levelComplete()

        // independent of states
        this.handleInput()
        time.tick()
        this.wrapObjects()
        draw.darkMode = window.matchMedia('(prefers-color-scheme: dark)').matches
    }

    levelComplete() {
        console.log("game.levelComplete() called")
        document.getElementById("level-complete").hidden = false
    }

    /***************
     * HANDLE INPUT
     ***************/
    handleInput() {
        if (Game.heldKeys[" "]) this.fireLaser()
        if (Game.heldKeys["ArrowLeft"]) this.ship.rotateLeft()
        if (Game.heldKeys["ArrowRight"]) this.ship.rotateRight()
        if (Game.heldKeys["ArrowUp"]) this.ship.thrust()

        if (Game.heldKeys[" "]) debug.display("{ }", "heldKey")
        if (Game.heldKeys["ArrowLeft"]) debug.display("{ArrowLeft}", "heldKey")
        if (Game.heldKeys["ArrowRight"]) debug.display("{ArrowRight}", "heldKey")
        if (Game.heldKeys["ArrowUp"]) debug.display("{ArrowUp}", "heldKey")
    }

    /**
     * HANDLE COLLISIONS
     */
    handleCollisions() {
        for (var i in this.rocks) {
            // collisions between ship and rocks
            if (!this.ship.invulnerable) {
                if (collisionHandler.distanceBetweenProjectiles(this.ship, this.rocks[i]) < this.ship.r + this.rocks[i].r) {
                    this.ship.hit()
                    this.rocks[i].hit()
                }
            }

            // collisions between lasers and rocks
            for (var j in this.lasers) {
                if (collisionHandler.distanceBetweenProjectiles(this.rocks[i], this.lasers[j]) < this.rocks[i].r + this.lasers[j].r) {
                    this.rocks[i].hit()
                    this.lasers[j].hit()
                }
            }
        }
        this.cleanUpZombies()
    }

    cleanUpZombies() {
        for (var i = 0; i < this.lasers.length; i++) {
            if (!this.lasers[i].alive) {
                this.lasers.splice(i, 1)
                break
            }
        }

        for (var i = 0; i < this.rocks.length; i++) {
            if (!this.rocks[i].alive) {

                // snapshot old rock so we can work with it
                var oldRock = this.rocks[i]

                // update the score!
                this.score += oldRock.points

                // split rock into two new ones (not yet added to collection)
                var newRocks = oldRock.split()
                console.log(newRocks)

                // remove old rock and splice new ones into its place in 'rocks' collection
                if (oldRock.id < 3)
                    this.rocks.splice(i, 1, newRocks[0], newRocks[1])
                else this.rocks.splice(i, 1)
                break // do NOT delete this, unless you want a nasty bug
            }
        }

        // debug.display(this.shipLives.length)
        if (!this.ship.alive) {
            this.ship = new Ship()
            if (this.shipLives.length > 0) this.shipLives.pop()
            else this.restart = true
        }
    }
    restart = false

    /**
     * WRAP
     */
    wrapObjects() {
        this.wrap(this.ship)
        this.lasers.forEach((laser) => this.wrap(laser))
        this.rocks.forEach((rock) => this.wrap(rock))
    }

    wrap(projectile) {
        var buffer = -projectile.radius
        if (projectile.p.x < buffer) {
            projectile.p.x = canvas.width - buffer
            return true
        } else if (projectile.p.x > canvas.width - buffer) {
            projectile.p.x = buffer
            return true
        }

        if (projectile.p.y < buffer) {
            projectile.p.y = canvas.height - buffer;
            return true
        } else if (projectile.p.y > canvas.height - buffer) {
            projectile.p.y = buffer;
            return true
        }

        return false
    }

    /**
     * LASERS
     */
    fireLaser() {
        if (!this.ship.laserDelayTimer > 0) {
            this.lasers.push(this.ship.fire())
                // debug.display(`asteroids.lasers.length{${this.lasers.length}}`, "lasersLength", false)
        }
    }

    /**
     * ROCKS
     */
    asteroidBelt(n) {
        for (var i = 0; i < n; i++) {
            this.rocks.push(new Rock())
        }
    }
}

export default Game