class Dimensions {
    constructor(w=0, h=0) {
        this.w = w
        this.h = h
    }

    get width()         { return this.w     }
    set width(new_w)    { this.w = new_w    }

    get height()        { return this.h     }
    set height(new_h)   { this.h = new_h    }
}

export default Dimensions