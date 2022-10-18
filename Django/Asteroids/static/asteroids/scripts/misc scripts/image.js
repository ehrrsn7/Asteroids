import draw         from "../draw.js"
import Dimensions   from "./dimensions.js"
import Point        from "./point.js"
const context = document.querySelector("canvas").getContext("2d")


class Image {
    constructor(
        filename="",
        id="unspecified image",
        dimensions=new Dimensions(0, 0),
        load=false) {
        
        // empty variables to hold information upon loadImage
        this.filename = filename
        this.imageElement = undefined
        this.dim = new Dimensions(0,0)

        // load if constructor arguments are specified
        if (filename == "") return
        if (load) this.loadImage(filename, id, dimensions)
    }

    loadImage(img_filename, id, dimensions) {
        // handle invalid filename
        if (this.filename == "") {
            var errorMsg = "Error: calling Image.loadImage with invalid filename"
            console.error(errorMsg)
            return
        }

        // initialize loading info
        console.log(`Loading image '${this.filename}'...`)
        this.filename   = img_filename
        this.dim        = dimensions

        // use draw.importImage to place image on the screen and save the img element location
        this.imageElement = draw.importImage(this.filename, id, this.dim)
    }

    display() { context.drawImage(this.imageElement, 0, 0) }

    displayAtPoint(gameobject_p=new Point(0,0), gameobject_a=0) {
        this.p = gameobject_p
        this.a = gameobject_a
        draw.rotateAndDraw(
            this.imageElement,
            this.p,
            this.dim, 
            this.a
        )
    }
}

export default Image