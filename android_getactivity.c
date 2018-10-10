/*
 * Sample for JNI calling.
 * Involve using the following functions
 * 	- SDL_AndroidGetJNIEnv()
 * 	- SDL_AndroidGetActivity()
 */

#include "SDL.h"
#include <jni.h>

void callJavaTestMethod()
{
	// retrieve the JNI environment
	JNIEnv* env = (JNIEnv*)SDL_AndroidGetJNIEnv();

	// retrieve the Java instance of the SDLActivity
	jobject activity = (jobject)SDL_AndroidGetActivity();

	// find the Java class of the activity. It should be SDLActivity or a subclass of it.
	jclass clazz = (*env)->GetObjectClass(env, activity);

	// find the identifier of the method to call
	// testMethod() will print "Print from testMethod() from Java code" in console
	jmethodID method_id = (*env)->GetMethodID(env, clazz, "testMethod", "()V");

	// effectively call the Java method
	(*env)->CallVoidMethod(env, activity, method_id);

	// clean up the local references
	(*env)->DeleteLocalRef(env, activity);
	(*env)->DeleteLocalRef(env, clazz);
}

int main(int argc, char *argv[]) {
	SDL_bool done;
	SDL_Window *window;
	SDL_Event event;					// Declare event handle

	SDL_Init(SDL_INIT_VIDEO);			// SDL2 initialization

	window = SDL_CreateWindow(	// Create a window
		"Sample Code for SDL",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);

	// Check that the window was successfully made
	if (window == NULL) {
		// In the event that the window could not be made...
		SDL_Log("Could not create window: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	done = SDL_FALSE;

	// user-defined code
	callJavaTestMethod();

	while (!done) {
		while (!done && SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT: {			// In case of exit
					done = SDL_TRUE;
					break;
				}
			}
		}
		SDL_Delay(17);
	}
	
	SDL_DestroyWindow(window);		// Close and destroy the window
	SDL_Quit();						// Clean up
	return 0;
}
