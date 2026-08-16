#include "SDL2/SDL_events.h"
#include "glad/glad.h"
#include <FelicoEngine/FelicoEngine.h>
#include <SDL2/SDL.h>
#include <cmath>

namespace FelicoEngine {
FelicoEngine::FelicoEngine(const char *title) { m_Title = title; }

bool FelicoEngine::init() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Error initializing SDL: %s\n", SDL_GetError());
    return false;
  }
  printf("SDL Initialized\n");

  SDL_DisplayMode mode;
  SDL_GetCurrentDisplayMode(0, &mode);
  m_Width = mode.w;
  m_Height = mode.h;
  m_Window = SDL_CreateWindow(m_Title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, m_Width, m_Height,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                                  SDL_WINDOW_FULLSCREEN_DESKTOP);
  if (!m_Window) {
    printf("Error creating window: %s\n", SDL_GetError());
    return false;
  }

  m_Context = SDL_GL_CreateContext(m_Window);
  if (!m_Context) {
    printf("Error creating GL context: %s\n", SDL_GetError());
    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;
    return false;
  }

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    SDL_GL_DeleteContext(m_Context);
    SDL_DestroyWindow(m_Window);
    m_Context = nullptr;
    m_Window = nullptr;
    return false;
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glViewport(0, 0, m_Width, m_Height);
  fprintf(stderr, "Viewport: 0,0 %dx%d\n", m_Width, m_Height);
  m_LastTick = SDL_GetTicks();
  return true;
}

void FelicoEngine::pollEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT)
      m_ShouldClose = true;
    else if (event.type == SDL_WINDOWEVENT &&
             event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
      m_Width = event.window.data1;
      m_Height = event.window.data2;
      glViewport(0, 0, m_Width, m_Height);
    }
  }
}

bool FelicoEngine::shouldClose() const { return m_ShouldClose; }

void FelicoEngine::beginFrame() {
  Uint32 now = SDL_GetTicks();
  m_DeltaTime = (now - m_LastTick) / 1000.0f;
  m_LastTick = now;
  m_DeltaTime = fminf(m_DeltaTime, 0.1f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void FelicoEngine::endFrame() { SDL_GL_SwapWindow(m_Window); }

void FelicoEngine::shutdown() {
  if (m_Context)
    SDL_GL_DeleteContext(m_Context);
  if (m_Window)
    SDL_DestroyWindow(m_Window);
  SDL_Quit();
}

int FelicoEngine::getWidth() const { return m_Width; }

int FelicoEngine::getHeight() const { return m_Height; }

float FelicoEngine::dt() const { return m_DeltaTime; }
FelicoEngine::~FelicoEngine() {}
} // namespace FelicoEngine
