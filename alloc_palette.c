/*
 * Demonstrate how to use SDL_AllocPalette function
 */

#include <SDL2/SDL.h>

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

	// -- user code section
	const int colors = 4;
	SDL_Palette* palette = SDL_AllocPalette(colors);
	SDL_Log("Palette's number of color: %d", palette->ncolors);

	// print color information as in palette
	SDL_Color tempColor;
	// note: all colors are initialized to be in white
	for (int i=0; i<colors; i++)
	{
		tempColor = palette->colors[i];
		SDL_Log("\tcolor at index %d => R:%u, G:%u, B:%u, A:%u\n", i, tempColor.r, tempColor.g, tempColor.b, tempColor.a);
	}
	// modify colors
	SDL_Color* colorPtr = NULL;
	colorPtr = palette->colors;

	// #1 black
	colorPtr->r = 0; colorPtr->g = 0; colorPtr->b = 0;
	// #2 red
	colorPtr = palette->colors + 1;
	colorPtr->r = 255; colorPtr->g = 0; colorPtr->b = 0;
	// #3 green
	colorPtr = palette->colors + 2;
	colorPtr->r = 0; colorPtr->g = 255; colorPtr->b = 0;
	// #4 blue
	colorPtr = palette->colors + 3;
	colorPtr->r = 0; colorPtr->g = 0; colorPtr->b = 255;

	// print all color information again
	SDL_Log("Colors after modification");
	for (int i=0; i<colors; i++)
	{
		tempColor = palette->colors[i];
		SDL_Log("\tcolor at index %d => R:%u, G:%u, B:%u, A:%u\n", i, tempColor.r, tempColor.g, tempColor.b, tempColor.a);

	}

	// free palette created with SDL_AllocPalette()
	SDL_FreePalette(palette);
	// -- end of user code section

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
