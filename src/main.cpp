#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <glad/glad.h>

int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Error initializing %s\n", SDL_GetError());
		return -1;
	}
	
	printf("SDL Initialized\n");
	SDL_Window* window;
	window = SDL_CreateWindow("FelicoEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		printf("Failed to initialize GLAD\n");
		return -1;
	}

	int shouldClose = false;

	while (!shouldClose) {
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) shouldClose = true;
		}

		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}