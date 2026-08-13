#pragma once

namespace FelicoEngine {
class Mesh {
public:
  Mesh(const float *vertices, unsigned int count);
  ~Mesh();
  void draw() const;

private:
  unsigned int m_VAO;
  unsigned int m_VBO;
  unsigned int m_vertexCount;
};
} // namespace FelicoEngine
