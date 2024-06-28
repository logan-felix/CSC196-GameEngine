#include "../../Engine/Source/Test.h"
#include <SDL.h>
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main(int argc, char* argv[])
{
	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	// create window
	// returns pointer to window if successful or nullptr if failed
	SDL_Window* window = SDL_CreateWindow("Game Engine",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600,
		SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// create renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);


	// DRAW TRIANGLES

	//while (true)
	//{
	//	// clear screen
	//	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	//	SDL_RenderClear(renderer);

	//	// draw triangles
	//	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	//	SDL_RenderDrawLine(renderer, 200, 450, 600, 450);
	//	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
	//	SDL_RenderDrawLine(renderer, 600, 450, 400, 150);
	//	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
	//	SDL_RenderDrawLine(renderer, 400, 150, 200, 450);
	//	
	//	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 0);
	//	SDL_RenderDrawLine(renderer, 300, 300, 400, 450);
	//	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
	//	SDL_RenderDrawLine(renderer, 400, 450, 500, 300);
	//	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);
	//	SDL_RenderDrawLine(renderer, 500, 300, 300, 300);

	//	// show screen
	//	SDL_RenderPresent(renderer);
	//}



	// DRAW RANDOM LINES AND POINTS
	
	while (true)
	{
		// clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		srand(time(NULL));

		// draw random points/lines
		for (int i = 0; i <= 100; i++) {
			SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, 0); // create random color
			SDL_RenderDrawPoint(renderer, rand() % 800, rand() % 600); // draw a point in a random location
			SDL_RenderDrawLine(renderer, rand() % 800, rand() % 600, rand() % 800, rand() % 600); // draw line between two random points
		}
		
		// show screen
		SDL_RenderPresent(renderer);
	}


	return 0;
}
