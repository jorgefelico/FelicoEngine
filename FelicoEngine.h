#ifndef FELICOENGINE_H
#define FELICOENGINE_H

#include <SDL2/SDL.h>

namespace FelicoEngine {

    class Engine {
        public:
            Engine();
            ~Engine();
            int OnExecute();
            bool OnInit();
            void OnEvent(SDL_Event *event);
            void OnLoop();
            void OnRender();
            void OnExit();
        private:
            bool isRunning;
            SDL_Window *pWindow;
            SDL_Renderer *pRenderer;
    };
}

#endif