#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace FelicoEngine {
class FelicoEngine {
public:
  FelicoEngine(const char *title);
  ~FelicoEngine();
  void init();
  void shutdown();
  int getWidth() const;
  int getHeight() const;
  void pollEvents();
  void beginFrame();
  void endFrame();
  bool shouldClose() const;

private:
  int m_Width;
  int m_Height;
  std::string m_Title;
  SDL_Window *m_Window;
  SDL_GLContext m_Context;
  bool m_ShouldClose = false;
};
} // namespace FelicoEngine
