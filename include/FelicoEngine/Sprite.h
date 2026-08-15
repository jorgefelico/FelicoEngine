#pragma once
#include "FelicoEngine/Camera.h"
#include <FelicoEngine/Mesh.h>
#include <FelicoEngine/Shader.h>
#include <FelicoEngine/Texture.h>
#include <FelicoEngine/Transform.h>

namespace FelicoEngine {
class Sprite {
public:
  Sprite(const char *name, float x, float y, float width, float height,
         const char *texturePath, Shader *shader, Camera *camera,
         Anchor anchor);
  ~Sprite();
  void draw();
  Transform &transform() { return m_Transform; };

private:
  const char *m_Name;
  Transform m_Transform;
  Texture m_Texture;
  Shader *m_Shader;
  Camera *m_Camera;
  static Mesh &getMesh();
  glm::mat4 buildModelMatrix();
};
} // namespace FelicoEngine
