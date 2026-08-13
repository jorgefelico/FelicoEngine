#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Error initializing %s", SDL_GetError());
		return -1;
	}
	
	printf("SDL Initialized");
	SDL_Window* window;
	window = SDL_CreateWindow("FelicoEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, NULL);
	
	int shouldClose = false;

	while (!shouldClose) {
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) shouldClose = true;
		}
	}

	// Cleanup
	SDL_Quit();
	return 0;
}