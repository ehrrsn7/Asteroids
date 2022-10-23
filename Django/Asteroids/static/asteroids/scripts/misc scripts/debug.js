const debugEl = document.getElementById("debug")

function addDOMTextElement(text, elementID, elementType) {
    console.warn("Creating new text element")
    let newElement = document.createElement(elementType)
    newElement.innerHTML = `[${elementID}] ${text}`
    newElement.id = elementID
    document.body.appendChild(newElement)
}

let insertString = (originalString, stringToAdd, index) => (
    originalString.slice(0, index) +
    stringToAdd +
    originalString.slice(index)
)


const debug = {
    DEBUG: false,
    toggleDebug: function() {
        this.DEBUG = !this.DEBUG
        if (this.DEBUG) {
            console.log("DEBUG enabled.")
            debugEl.style.visibility = "visible"
            this.display("Debug:", "feedback", "h2")
        } else {
            console.log("DEBUG disabled.")
            debugEl.style.visibility = "hidden"
        }
    },
    log: function(txt, debug_msg = true) {
        var text = " "
        if (debug_msg) text = "debug: "
        text += txt + " "
        if (this.DEBUG) console.warn(text)
    },
    update: function() {

    },
    display: function(text, id = "user feedback", elementType = "h3", insert = false) {
        if (!this.DEBUG) return

        // get element
        let element = document.getElementById(id)

        // if element doesn't exist, create one
        if (element === null) addDOMTextElement(text, id, elementType)

        // display text
        else element.innerHTML = `[${element.id}]: ${text}`

        debugEl.appendChild(element)
    }
}

export default debug