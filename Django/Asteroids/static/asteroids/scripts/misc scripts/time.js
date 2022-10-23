import debug from "./debug.js"
import FPS from "../main.js"

const Time = {
    currentTime: new Date(),
    deltaTime: 0.0,
    slowRateTimer: 0.0,

    tick() {
        // update currentTime and deltaTime
        var previousTime    = this.currentTime
        this.currentTime    = new Date()
        this.deltaTime      = (this.currentTime - previousTime) / 1000

        // handle slow rate timer
        if (this.slowRateTimer <= 0.0) this.slowRateTimer = .1
        else this.slowRateTimer -= this.deltaTime

        // debug
        if (this.slowRateTimer == .1)
            debug.display("fps = " + FPS*FPS*this.deltaTime + " s", "deltaTime")
    }
}

export default Time