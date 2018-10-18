/*
 *  rectangles.c
 *  written by Holmes Futrell
 *  use however you want
 *
 *  modified
 *  as on Android (as tested on Huawei P9 Lite)
 *  if not clear screen every frame, it's flickering
 *  so now it will show one new rectangle for every 5 seconds,
 *  before it clears and repeats the cycle.
*/

#include "SDL.h"
#include <time.h>
#include "common.h"

unsigned int lastTime = 0, currentTime;
SDL_Rect drawingRect;
SDL_Color color;

void
render(SDL_Renderer *renderer)
{
	/* Get current time since SDL library initialized */
	currentTime = SDL_GetTicks();
	/* Check if we should render randomly rectangle */
	if (lastTime == 0 || currentTime > lastTime + 5000)
	{
		int renderW;
		int renderH;

		SDL_RenderGetLogicalSize(renderer, &renderW, &renderH);

		/*  Come up with a random rectangle */
		drawingRect.w = randomInt(64, 128);
		drawingRect.h = randomInt(64, 128);
		drawingRect.x = randomInt(0, renderW);
		drawingRect.y = randomInt(0, renderH);

		/* Come up with a random color */
		color.r = randomInt(50, 255);
		color.g = randomInt(50, 255);
		color.b = randomInt(50, 255);

		/*  Fill the rectangle in the color */
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
		SDL_RenderFillRect(renderer, &drawingRect);

		lastTime = currentTime;
	}
	// otherwise draw the previous rect
	else
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
		SDL_RenderFillRect(renderer, &drawingRect);
	}

    /* update screen */
    SDL_RenderPresent(renderer);
}

int
main(int argc, char *argv[])
{

    SDL_Window *window;
    SDL_Renderer *renderer;
    int done;
    SDL_Event event;
    int windowW;
    int windowH;

    /* initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fatalError("Could not initialize SDL");
    }

    /* seed random number generator */
    srand(time(NULL));

    /* create window and renderer */
    window = SDL_CreateWindow(NULL, 0, 0, 320, 480, SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == 0) {
        fatalError("Could not initialize Window");
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        fatalError("Could not create renderer");
    }

    SDL_GetWindowSize(window, &windowW, &windowH);
    SDL_RenderSetLogicalSize(renderer, windowW, windowH);

    /* Enter render loop, waiting for user to quit */
    done = 0;
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = 1;
            }
        }

		/* Fill screen with black */
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
		SDL_RenderClear(renderer);

        render(renderer);
    }

    /* shutdown SDL */
    SDL_Quit();

    return 0;
}
