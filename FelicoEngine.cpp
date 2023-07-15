#include "FelicoEngine.h"

namespace FelicoEngine {

    Engine::Engine() {
        isRunning = true;
        pWindow = NULL;
        pRenderer = NULL;
    }

    bool Engine::OnInit() {
        if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            return false;
        }

        pWindow = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,800,800,SDL_WINDOW_SHOWN);
        if(pWindow != NULL) {
            pRenderer = SDL_CreateRenderer(pWindow,-1,0);
        } else {
            return false;
        }

        return true;
    }

    int Engine::OnExecute() {
        SDL_Event event;

        if(OnInit() == false) {
            return -1;
        }

        while(isRunning) {
            while(SDL_PollEvent(&event) != 0) {
                OnEvent(&event);
            }

            OnLoop();
            OnRender();
        }

        return 1;
    }

    void Engine::OnEvent(SDL_Event *event) {
        if(event->type == SDL_QUIT) {
            isRunning = false;
        }
    }

    void Engine::OnLoop() {

    }

    void Engine::OnRender() {
        SDL_SetRenderDrawColor(pRenderer,255,255,255,255);
        SDL_RenderClear(pRenderer);
        SDL_RenderPresent(pRenderer);
    }

    void Engine::OnExit() {
        SDL_DestroyRenderer(pRenderer);
        SDL_DestroyWindow(pWindow);
        pWindow = NULL;
        SDL_Quit();
    }
}