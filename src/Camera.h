#pragma once
#include "ext/matrix_float4x4.hpp"

namespace FelicoEngine {
class Camera {
public:
  Camera(int width, int height);
  glm::mat4 getProjectionMatrix();

private:
  unsigned int m_Width;
  unsigned int m_Height;
  glm::mat4 m_Projection;
};
} // namespace FelicoEngine
