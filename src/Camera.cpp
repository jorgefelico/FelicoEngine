#include "Camera.h"
#include "ext/matrix_clip_space.hpp"

namespace FelicoEngine {
Camera::Camera(int width, int height) {
  m_Width = width;
  m_Height = height;
  m_Projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
}

glm::mat4 Camera::getProjectionMatrix() { return m_Projection; }
} // namespace FelicoEngine
