# Overview

Asteroids!

This is a Game that I made (cloned from the Atari Game) as an android app.

[Demonstration video, pt 1 - https://www.youtube.com/watch?v=5OCiM1h7AJI](https://www.youtube.com/watch?v=5OCiM1h7AJI)
[Demonstration video, pt 2 - https://www.youtube.com/watch?v=WnqdI3prlWI](https://www.youtube.com/watch?v=WnqdI3prlWI)

# Development Environment

Developed using Android Studio

Coded in Kotlin (layout in XML, compiled to java for app/final product)

# Useful Websites

## Reference code: I used this for the overall structure for my code.
- http://gamecodeschool.com/kotlin/coding-a-space-invaders-game-in-kotlin/

## assets I got from online
Asteroid
- http://pixelartmaker.com/art/b02b88d8461a4fb

## Other more useful links
programmatically getting the device screen width/height 
- https://www.tutorialkart.com/kotlin-android/get-screen-width-and-height-programmatically-example/

Documentation for the first class that ```Game``` inherits (```SurfaceView```)
- https://developer.android.com/reference/android/view/SurfaceView 

Documentation for the second class that ```Game``` inherits (```Runnable```)
- https://developer.android.com/reference/java/lang/Runnable

```companion object```
- https://medium.com/@ansujain/kotlin-how-to-create-static-members-for-class-543d0f126f7c 

Drawables in Android
- https://developer.android.com/guide/topics/graphics/drawable-animation

Rect class in Android
- https://developer.android.com/reference/android/graphics/Rect

Button widget in Android
- https://developer.android.com/reference/kotlin/android/widget/Button

## more useful links
* Tutorial for learning how a basic app is made (developer.android.com) - https://developer.android.com/training/basics/firstapp
* Explanation of what "activities" are - https://www.c-sharpcorner.com/article/how-to-be-working-with-multiple-activities-and-navigate-the-activities-in-androi/
* I got lost and didn't know where to find the 'assets' folder (following the tutorial above). This site explains where to insert one - https://stackoverflow.com/questions/18302603/where-to-place-the-assets-folder-in-android-studio
* [BUG FIX: 'no resource found that matches the given name'] - https://stackoverflow.com/questions/4736523/no-resource-found-that-matches-the-given-name
* For game loop: stackoverflow.com how to get accurate deltaTime  - https://stackoverflow.com/questions/37678799/how-to-get-accurate-deltatime-in-java
* data type casting in kotlin: toLong (an example of one cast I needed) - https://kotlinlang.org/api/latest/jvm/stdlib/kotlin/-float/to-long.html
* [BUG FIX: ASTEROIDS WOULDN'T RUN]  - https://stackoverflow.com/questions/21814825/you-need-to-use-a-theme-appcompat-theme-or-descendant-with-this-activity
* Tutorial on how to draw basic shapes using canvas and paint (not very successful) - https://www.tutorialkart.com/kotlin-android/draw-circle-border-example/
* [BUG: why wouldn't Runnable::onDraw() get called?] - https://stackoverflow.com/questions/11912406/view-ondraw-when-does-it-get-called
* Kotlin Getters/setters (still don't know how these work, they look similar to javascript getters/setters but don't work the same) - https://www.geeksforgeeks.org/kotlin-setters-and-getters/
* 🙌🏽 Loading the VSCode keymap in IntelliJ/Android Studio 🙌🏽 - https://plugins.jetbrains.com/plugin/12062-vscode-keymap
* More information on getting device screen width/height programmatically - https://stackoverflow.com/questions/3190581/obtaining-surfaceview-dimensions
* Kotlin Random library documentation - https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.random/-random/
* Kotlin 'collections' - http://www.androidcoding.in/2019/02/23/android-dynamic-list/
* Kotlin 'for-loops' - https://www.programiz.com/kotlin-programming/for-loop
* Solutions for animating bitmaps - https://stackoverflow.com/questions/11482955/animating-bitmap-image-in-android
* Adding event listeners to buttons Kotlin Android - https://www.youtube.com/watch?v=QmEjLiR2rGU

# Future Work

* Something I could have done better: getting experienced developer help at a more ideal time (I got help, but I would have gotten a lot farther if I had reached out a little earlier)
* Future plans: 
    - Make the game playable with user interaction
    - Change MainActivity to be a workable 'main menu' screen
    - clean up the code I currently have and make the files cleaner
