#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace FelicoEngine {
class FelicoEngine {
public:
  FelicoEngine(const char *title);
  ~FelicoEngine();
  bool init();
  void shutdown();
  int getWidth() const;
  int getHeight() const;
  void pollEvents();
  void beginFrame();
  void endFrame();
  bool shouldClose() const;
  float dt() const;

private:
  int m_Width;
  int m_Height;
  std::string m_Title;
  SDL_Window *m_Window = nullptr;
  SDL_GLContext m_Context = nullptr;
  bool m_ShouldClose = false;
  float m_DeltaTime = 0.0f;
  Uint32 m_LastTick = 0;
};
} // namespace FelicoEngine
