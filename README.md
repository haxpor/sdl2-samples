# SDL2 Sample Code

Sample code along the way of finishing [sdl2-manpage](https://github.com/haxpor/sdl2-manpage)

* Compile and build executable with `gcc -lsdl2 <source-file.c>`
* Clean your local working directory with `make clean`

# Android

To test on android

* symlink your SDL2 source code directory to `android-project/app/jni` - do this once
* copy testing `.c` source file into `android-project/app/jni/src`
* modify `Android.mk` in `android-project/app/jni/src` to include testing source file, see comment in the file
* execute `./gradlew installDebug` to build and install the app on your Android device

# License
MIT, Wasin Thonkaew
