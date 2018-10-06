#include <SDL2/SDL.h>

struct Param
{
	Uint64 value;
};
struct Param myParam;

Uint32 myTimerCallback(Uint32 interval, void *param)
{
	// get information from param
	if (param != NULL) {
		struct Param* castedParam = ((struct Param*)param);
		SDL_Log("hey, get %llu", castedParam->value);
	}
	else {
		SDL_Log("hey, with no param");
	}
	
	SDL_Event event;
	SDL_UserEvent userevent;

	userevent.type = SDL_USEREVENT;
	userevent.code = 0;
	userevent.data1 = NULL;
	userevent.data2 = NULL;

	event.type = SDL_USEREVENT;
	event.user = userevent;

	// push user-defined event to trigger another
	SDL_PushEvent(&event);
	return interval;
}

void userdefinedCode()
{
	// set value of parameter
	myParam.value = 1;

	Uint32 delay = (2000 / 10) * 10;
	SDL_TimerID myTimer = SDL_AddTimer(delay, myTimerCallback, (void*)&myParam);
}

int main(int argc, char *argv[]) {
	SDL_bool done;
	SDL_Window *window;
	SDL_Event event;					// Declare event handle

	SDL_Init(SDL_INIT_VIDEO);			// SDL2 initialization

	window = SDL_CreateWindow(	// Create a window
		"Genearl test for SDL2",
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

	// add user defined code for this sample app here
	userdefinedCode();

	while (!done) {
		while (!done && SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT: {			// In case of exit
					done = SDL_TRUE;
					break;
				}
			}
		}
		SDL_Delay(16);
	}
	
	SDL_DestroyWindow(window);		// Close and destroy the window
	SDL_Quit();						// Clean up
	return 0;
}
