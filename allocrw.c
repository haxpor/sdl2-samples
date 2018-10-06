/*
 * Sample code for SDL_AllocRW API
 * Use related functions as follows to call functions of SDL_RWops*
 * - SDL_RWsize
 * - SDL_RWread
 * - SDL_RWseek
 * - SDL_RWwrite
 * - SDL_RWclose
 * - SDL_RWtell
 *
 * Implementations of SDL_RWops is up to user.
 */

#include <SDL2/SDL.h>

/* These functions should not be used except from pointers in an SDL_RWops */
static Sint64 mysizefunc(SDL_RWops *context)
{
  return -1;
}

static Sint64 myseekfunc(SDL_RWops *context, Sint64 offset, int whence)
{
  return SDL_SetError("Can't seek in this kind of SDL_RWops");
}

static size_t myreadfunc(SDL_RWops *context, void *ptr, size_t size, size_t maxnum)
{
  SDL_memset(ptr, 0, size*maxnum);
  return maxnum;
}

static size_t mywritefunc(SDL_RWops *context, const void *ptr, size_t size, size_t num)
{
  return num;
}

static int myclosefunc(SDL_RWops *context)
{
  if (context->type != 0xdeadbeef)
  {
    return SDL_SetError("Wrong kind of SDL_RWops for myclosefunc()");
  }

  free(context->hidden.unknown.data1);
  SDL_FreeRW(context);
  return 0;
}

SDL_RWops* MyCustomRWop()
{
  SDL_RWops *c = SDL_AllocRW();
  if (c == NULL) return NULL;

  c->size = mysizefunc;
  c->seek = myseekfunc;
  c->read = myreadfunc;
  c->write = mywritefunc;
  c->close = myclosefunc;
  c->type = 0xdeadbeef;
  c->hidden.unknown.data1 = malloc(256);
  return c;
}

void usercode()
{
	// user code section
	SDL_RWops *myRWops = MyCustomRWop();
	// - size
	SDL_Log("size: %lld", SDL_RWsize(myRWops));
	
	// - seek
	SDL_RWseek(myRWops, 0, RW_SEEK_SET);
	SDL_Log("%s", SDL_GetError());

	// - read
	void* readBuffer = malloc(256);
	size_t read = SDL_RWread(myRWops, readBuffer, 1, 256);
	SDL_Log("read: %zu", read);

	// - write
	size_t write = SDL_RWwrite(myRWops, (const void*)readBuffer, 1, 256);
	SDL_Log("write: %zu", write);

	// free
	free(readBuffer);
	// - close	
	SDL_RWclose(myRWops);
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

	// execute user code inside this function
	usercode();

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
