// import
import math from "./misc scripts/math.js"
import debug from "./misc scripts/debug.js";
import stateManager from "./stateManager.js";
const bodyTag = document.querySelector("body")
const canvas = document.querySelector("canvas")
const context = canvas.getContext("2d")

// draw module
var draw = {

    drawImages: false,
    darkMode: window.matchMedia('(prefers-color-scheme: dark)').matches,

    rotateAndDraw: function(img, p, dim, a) {
        console.log("Rotate and draw() called")

        // use context save() and restore() to make sure only image is being rotated
        context.save()

        // translate & rotate
        context.translate(p.x, p.y)
        context.rotate(a)

        // draw image with image center on specified x and y coordinates
        context.drawImage(img, p.x, p.y, dim.w, dim.h)

        // restore canvas
        context.translate(-p.x, -p.y)
        context.rotate(-a)
        context.restore()
    },

    importImage: function(imageFilename, id, gameobject_dimensions) {
        let imageElement = document.createElement("img")
        imageElement.src = imageFilename
        imageElement.id = id
        canvas.appendChild(imageElement)
        return imageElement
    },

    colors: {
        darkMode: {
            color: "white",
            pauseColor: "rgb(230, 230, 230)",
            background: "rgb(5, 10, 15)",
            pauseBackground: "rgb(20, 20, 20)"
        },
        lightMode: {
            color: "white",
            pauseColor: "rgb(20, 20, 20)",
            background: "rgb(5, 10, 15)",
            pauseBackground: "rgb(230, 230, 230)"
        }
    },

    get color() {
        if (stateManager.currentState == 2)
            return this.darkMode ? this.colors.darkMode.pauseColor : this.colors.lightMode.pauseColor
        else
            return this.darkMode ? this.colors.darkMode.color : this.colors.lightMode.color
    },

    get canvasColor() {
        if (stateManager.currentState == 2)
            return this.darkMode ? this.colors.darkMode.pauseBackground : this.colors.lightMode.pauseBackground
        else
            return this.darkMode ? this.colors.darkMode.background : this.colors.lightMode.background
    },

    fillBackground: function() {
        context.fillStyle = this.canvasColor
        context.fillRect(0, 0, canvas.width, canvas.height)
    },

    drawText: function(text, xOffset = 0, yOffset = 30) {
        context.fillStyle = this.color
        var fontSize = 24
        context.font = `${fontSize}px calibri`
        context.fillText(
            // text
            text,
            // x (center align)
            canvas.width * .5 - fontSize * `${text}`.length * .5 + xOffset,
            // y
            yOffset
        )
    },

    triangle: function(
        p, // point
        sl, // side length
        a, // angle (radians)
        color = "unspecified",
        thickness = 1.75
    ) {

        a += math.rad(90)
        if (color == "unspecified") color = this.color
        context.fillStyle = "black"

        // draw a triangular ship
        context.strokeStyle = color
        context.lineWidth = thickness
        context.beginPath()
        context.moveTo(
            // (jump to) nose of the ship
            p.x + (4 / 3) * sl * Math.cos(a),
            p.y - (4 / 3) * sl * Math.sin(a)
        )
        context.lineTo(
            // (draw to) rear left of the ship
            p.x - sl * ((2 / 3) * Math.cos(a) + Math.sin(a)),
            p.y + sl * ((2 / 3) * Math.sin(a) - Math.cos(a))
        )
        context.lineTo(
            // (draw to) rear right of the ship
            p.x - sl * ((2 / 3) * Math.cos(a) - Math.sin(a)),
            p.y + sl * ((2 / 3) * Math.sin(a) + Math.cos(a))
        )
        context.closePath()
        context.stroke()
        context.fill()
    },

    star(p, r, color = "white") {
        var fill = true
        context.strokeStyle = color
        if (fill) context.fillStyle = color
        context.lineWidth = 1.5
        context.beginPath()
        context.arc(p.x, p.y, r, 0, math.rad(360), false)
        context.closePath()
        context.stroke()
        if (fill) context.fill()
    },

    showBounding: false,

    circle: function(p, r, fill = false, color = "unspecified") {
        if (color == "unspecified") color = this.color
        context.strokeStyle = color
        if (fill) context.fillStyle = color
        context.lineWidth = 1.5
        context.beginPath()
        context.arc(p.x, p.y, r, 0, math.rad(360), false)
        context.closePath()
        context.stroke()
        if (fill) context.fill()
    },

    point: function(x, y) {
        if (x === y === NaN) {
            console.error("In draw.point(): invalid input for 'p'")
            return
        }
        context.strokeStyle = "black"
        context.fillRect(x, y, 1, 1)
    },

    rock: function(x, y, r, a, vertices, color = "slategrey") {

        // update draw info to draw rock
        context.strokeStyle = "slategrey"
        context.lineWidth = 1.5
        context.fillStyle = this.canvasColor

        // draw a path
        context.beginPath();

        context.moveTo(
            x + r * Math.cos(math.rad(a)),
            y + r * Math.sin(math.rad(a))
        )

        var r = 75
        vertices.forEach((vertex) => {
            context.lineTo(
                x + vertex.offset * Math.cos(math.rad(vertex.angle + a)),
                y + vertex.offset * Math.sin(math.rad(vertex.angle + a))
            )
        })

        // tell canvas to paint the paths
        context.closePath();
        context.stroke();
        context.fill()
    }

}

// export draw object module
export default draw