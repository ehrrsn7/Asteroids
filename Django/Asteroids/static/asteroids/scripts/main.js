// import
import debug from "./misc scripts/debug.js"

// define
const FPS = 60
export default FPS

/************
 * GAME LOOP
 ************/
import Game from "./asteroids.js"
import draw from "./draw.js"
var asteroids = new Game()
setInterval(() => {
    asteroids.update()
    if (asteroids.restart == true) restart()
})

/****************
 * INPUT MANAGER
 ****************/

// keyboard input
document.addEventListener("keydown", keyDown)

// key up (remove keys)
document.addEventListener("keyup", keyUp)

function keyDown(event) {
    Game.heldKeys[event.key] = true
        // debug.display(`heldKeys {${event.key}} <- true`)
    if (event.key.toLowerCase() == "r") restart()
    if (event.key.toLowerCase() == "d") debug.toggleDebug()
}

function keyUp(event) {
    Game.heldKeys[event.key] = false
        // debug.display(`heldKeys {${event.key}} <- false`)
}

export function restart() {
    debug.display("restarting game", "user feedback", "h3")
    asteroids = new Game()
}