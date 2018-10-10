/*
 * Sample for testing following functions
 * - SDL_AndroidGetExternalStoragePath
 * - SDL_AndroidGetExternalStorageState
 * - SDL_AndroidGetInternalStoragePath
 */

#include "SDL.h"

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
	SDL_Log("Android's external storage path: %s", SDL_AndroidGetExternalStoragePath());
	int storageState = SDL_AndroidGetExternalStorageState();
	if ((storageState & SDL_ANDROID_EXTERNAL_STORAGE_READ) == SDL_ANDROID_EXTERNAL_STORAGE_READ) {
		SDL_Log("- external storage is readable");
	}
	if ((storageState & SDL_ANDROID_EXTERNAL_STORAGE_WRITE) == SDL_ANDROID_EXTERNAL_STORAGE_WRITE) {
		SDL_Log("- external storage is writeable");
	}

	SDL_Log("Android's internal storage path: %s", SDL_AndroidGetInternalStoragePath());

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
