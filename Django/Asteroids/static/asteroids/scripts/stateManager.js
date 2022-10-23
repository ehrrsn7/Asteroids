import draw from "./draw.js"
import Dimensions from "./misc scripts/dimensions.js"
import GameObject from "./misc scripts/gameObject.js"
import Point from "./misc scripts/point.js"

// helper class
class state {
    constructor(name, state_i) {
        this.name = name
        this.state = state_i
    }
}

// Asteroids Game States
class Scene {
    // here, scene is to be the base object for all states
    // (all states must have a scene to work with)
    constructor() {
        this.backgroundImage = new Image(
            "../assets/stars.png",
            "background image",
            new Dimensions(0, 0),
            true)
    }


    update() {
        this.display()
    }

    display() {
        this.drawBackground()
    }

    drawBackground() {
        if (draw.drawImages)
            this.backgroundImage.display()
        else draw.fillBackground()
    }
}


class Resume extends Scene {

}

class Pause extends Scene {

}

class MainMenu extends Scene {

}

class SettingsState extends Scene {

}


// state manager module
const stateManager = {
    currentState: 0,
    get state() { return this.states[this.currentState] },
    states: [
        new state("resume", new Resume()),
        new state("pause", new Pause()),
        new state("main menu", new MainMenu()),
        new state("settings menu", new SettingsState())
    ]
}

export default stateManager


// ship lives
class ShipLife extends GameObject {
    constructor(x) {
        super()
        this.name = "ship life"
        this.p = new Point(x, 20)
        this.r = 10
        this.a = 0
    }

    display() {
        super.display()
        draw.triangle(this.p, this.r, this.a)
    }
}

export function loadShipLives(n) {
    var newLivesArray = []
    for (var i = 1; i < n + 1; i++) {
        newLivesArray.push(
            new ShipLife(i * 30)
        )
    }
    return newLivesArray
}