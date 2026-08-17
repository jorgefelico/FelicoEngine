#include "FelicoEngine/Mesh.h"
#include "FelicoEngine/Shader.h"
#include "FelicoEngine/Texture.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float2.hpp"
#include <FelicoEngine/Sprite.h>
#include <glm/gtc/matrix_transform.hpp>

namespace FelicoEngine {

Sprite::Sprite(const char *name, float x, float y, float width, float height,
               Atlas *atlas, Shader *shader, Camera *camera,
               Anchor anchor)
    : m_Name(name), m_Atlas(atlas), m_Shader(shader), m_Camera(camera) {
  m_Transform.position = {x, y};
  m_Transform.scale = {width, height};
  m_Transform.anchor = anchor;
}

void Sprite::draw() {
  m_Atlas->getTexture().bind(0);

  glm::mat4 model = buildModelMatrix();
  m_Shader->use();
  m_Shader->setMat4("u_projection", m_Camera->getProjectionMatrix());
  m_Shader->setMat4("u_model", model);
  m_Shader->setMat4("u_view", m_Camera->getViewMatrix());
  m_Shader->setVec4("u_uvRect", m_UvRect);
  getMesh().draw();
}

Mesh &Sprite::getMesh() {
  static float quad[] = {
      // x,    y,    r, g, b, u,    v
      0.0f, 0.0f, 1, 1, 1, 0.0f, 0.0f, // top-left
      1.0f, 0.0f, 1, 1, 1, 1.0f, 0.0f, // top-right
      1.0f, 1.0f, 1, 1, 1, 1.0f, 1.0f, // bottom-right

      0.0f, 0.0f, 1, 1, 1, 0.0f, 0.0f, // top-left
      1.0f, 1.0f, 1, 1, 1, 1.0f, 1.0f, // bottom-right
      0.0f, 1.0f, 1, 1, 1, 0.0f, 1.0f, // bottom-left
  };

  static Mesh mesh(quad, sizeof(quad) / sizeof(quad[0]));
  return mesh;
}

glm::mat4 Sprite::buildModelMatrix() {
  glm::vec2 anchor = m_Transform.getAnchor();
  glm::mat4 matrix =
      glm::translate(glm::mat4(1),
                     {m_Transform.position.x, m_Transform.position.y, 0}) *
      glm::rotate(glm::mat4(1), m_Transform.rotation, {0, 0, 1}) *
      glm::scale(glm::mat4(1), {m_Transform.scale.x, m_Transform.scale.y, 1}) *
      glm::translate(glm::mat4(1), {anchor.x, anchor.y, 0});

  return matrix;
}

void Sprite::setUvRect(float x, float y, float width, float height) {
  int W = m_Atlas->getTexture().width();
  int H = m_Atlas->getTexture().height();
  if (W == 0 || H == 0)
    return;
  m_UvRect = {x / W, 1.0f - (y + height) / H, width / W, height / H};
}
void Sprite::setFrame(int index) {
  AtlasRect rect = m_Atlas->getFrame(index);
  setUvRect(rect.x, rect.y, rect.w, rect.h);
};

void Sprite::setRegion(const char *name) {
  AtlasRect rect = m_Atlas->getRegion(name);
  setUvRect(rect.x, rect.y, rect.w, rect.h);
};

Sprite::~Sprite() {}
} // namespace FelicoEngine
