#include "Mesh.h"
#include "glad/glad.h"

namespace FelicoEngine {
Mesh::Mesh(const float *vertices, unsigned int count) {
  m_vertexCount = count;
  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);
  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(float), vertices,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
                        (void *)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
                        (void *)(5 * sizeof(float)));
  glEnableVertexAttribArray(2);
  glBindVertexArray(0);
}

void Mesh::draw() const {
  glBindVertexArray(m_VAO);
  glDrawArrays(GL_TRIANGLES, 0, m_vertexCount / 7);
  glBindVertexArray(0);
}

Mesh::~Mesh() {
  glDeleteVertexArrays(1, &m_VAO);
  glDeleteBuffers(1, &m_VBO);
}
} // namespace FelicoEngine
