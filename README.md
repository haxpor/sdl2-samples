# SDL2 Sample Code

Sample code along the way of finishing [sdl2-manpage](https://github.com/haxpor/sdl2-manpage)

* Compile and build executable with `gcc -lsdl2 <source-file.c>`
* Clean your local working directory with `make clean`

# Android

To test on android

We have two android project for version 2.0.8 and 2.0.9 (development snapshot as of 1 Oct 2018). Choose one that is suitable for your sample code.

* symlink your SDL2 source code directory to `android-project/app/jni` - do this once
* copy testing `.c` source file into `android-project/app/jni/src`
* modify `Android.mk` in `android-project/app/jni/src` to include testing source file, see comment in the file
* execute `./gradlew installDebug` to build and install the app on your Android device

To test on ios

* remove broken of included sub-project as seen in project navigation pane
* add `<your SDL source directory>/Xcode-iOS/SDL/SDL.xcodeproj` as a sub-project
* add more sdl2 sample source code into `src` directory by right click and add files in Xcode
* set "Header Search Path" in Build Settings for your target properly, it should be aligned with headers as referenced by SDL project as you recently added
* create a new target if needed to run each new sample as you added

> There is rectangles sample already added there, so you can see for example.

You can read more about how to manually come up with this iOS sample project from my blog [here](https://blog.wasin.io/2018/10/19/build-sdl2-application-on-ios.html).

# License
MIT, Wasin Thonkaew
