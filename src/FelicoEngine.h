#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace FelicoEngine {
class FelicoEngine {
public:
  FelicoEngine(const char *title, unsigned int width, unsigned int height);
  ~FelicoEngine();
  void init();
  void run();
  void shutdown();

private:
  unsigned int m_Width;
  unsigned int m_Height;
  std::string m_Title;
  SDL_Window *m_Window;
  SDL_GLContext m_Context;
};
} // namespace FelicoEngine
