#pragma once
#include <glm/ext/matrix_float4x4.hpp>

namespace FelicoEngine {
class Camera {
public:
  Camera(int width, int height);
  glm::mat4 getProjectionMatrix();
  glm::mat4 getViewMatrix();
  void setPosition(glm::vec2 pos);
  void resize(int width, int height);

private:
  unsigned int m_Width;
  unsigned int m_Height;
  glm::mat4 m_Projection;
  glm::vec2 m_Position;
  glm::mat4 m_ViewMatrix;
};
} // namespace FelicoEngine
