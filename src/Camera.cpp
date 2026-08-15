#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <FelicoEngine/Camera.h>

namespace FelicoEngine {
Camera::Camera(int width, int height) {
  m_Width = width;
  m_Height = height;
  m_Projection =
      glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
  m_Position = {width / 2, height / 2};
}

void Camera::setPosition(glm::vec2 pos) { m_Position = pos; }
glm::mat4 Camera::getViewMatrix() {
  m_ViewMatrix =
      glm::translate(glm::mat4(1), {m_Width / 2.0f - m_Position.x,
                                    m_Height / 2.0f - m_Position.y, 0.0f});
  return m_ViewMatrix;
};
glm::mat4 Camera::getProjectionMatrix() { return m_Projection; }
} // namespace FelicoEngine
