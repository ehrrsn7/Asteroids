import debug from "./misc scripts/debug.js"
import math from "./misc scripts/math.js"

const collisionManager = {
    distanceBetweenProjectiles(proj1, proj2) {
        return math.dist(proj1.p, proj2.p)
    },

    hasCollided(proj1, proj2) {
        // debug.display(proj1.name + " collided with " + proj2 + " name.")
        return (this.distanceBetweenProjectiles(proj1, proj2) > proj1.r + proj2.r)
    }
}

export default collisionManager