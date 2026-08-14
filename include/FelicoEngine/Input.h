#pragma once
#include <SDL2/SDL_scancode.h>

namespace FelicoEngine {
class Input {
public:
  void poll();
  bool isKeyDown(SDL_Scancode key) const;
  bool isKeyPressed(SDL_Scancode key) const;

private:
  bool m_Current[SDL_NUM_SCANCODES] = {};
  bool m_Previous[SDL_NUM_SCANCODES] = {};
};
} // namespace FelicoEngine
