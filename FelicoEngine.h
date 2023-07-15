#ifndef FELICOENGINE_H
#define FELICOENGINE_H

#include <SDL2/SDL.h>
#include <iostream>

namespace FelicoEngine {

    class Engine {
        public:
            Engine(std::string title, int width, int height);
            ~Engine();
            int OnExecute();
            bool OnInit();
            void OnEvent(SDL_Event *event);
            void OnLoop();
            void OnRender();
            void OnExit();
        private:
            std::string mTitle;
            int mWidth;
            int mHeight;
            bool isRunning;
            SDL_Window *pWindow;
            SDL_Renderer *pRenderer;
    };
}

#endif