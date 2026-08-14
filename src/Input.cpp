#include <FelicoEngine/Input.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <cstring>

namespace FelicoEngine {
void Input::poll() {
  memcpy(m_Previous, m_Current, sizeof(m_Current));
  const Uint8 *state = SDL_GetKeyboardState(nullptr);
  for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
    m_Current[i] = (state[i] != 0);
  }
}

bool Input::isKeyPressed(SDL_Scancode key) const {
  return m_Current[key] && !m_Previous[key];
}
bool Input::isKeyDown(SDL_Scancode key) const { return m_Current[key]; }
} // namespace FelicoEngine
