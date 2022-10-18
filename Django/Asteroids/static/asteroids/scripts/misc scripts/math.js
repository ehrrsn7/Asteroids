const math = {
    rad: function(angleDegrees) { return angleDegrees * Math.PI / 180 },
    deg: function(angleRadians) { return angleRadians * 180 / Math.PI },
    mag: function(x, y)         { return Math.sqrt((Math.pow(x, 2)) + (Math.pow(y, 2))) },
    randomrange: function(a, b) { return a + ((b - a) * Math.random()) },
    dist: function(p1, p2)      { return this.mag((p2.x - p1.x), (p2.y - p1.y)) }
}

export default math