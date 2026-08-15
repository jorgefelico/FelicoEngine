#pragma once

#include "glm/ext/matrix_float4x4.hpp"

namespace FelicoEngine {
class Shader {
public:
  Shader(const char *vertPath, const char *fragPath);
  ~Shader();

  void use() const;
  void setMat4(const char *name, glm::mat4 value);

private:
  unsigned int m_ID;
  unsigned int m_vertShader;
  unsigned int m_fragShader;
  void createVertShader(const char *vertPath);
  void createFragShader(const char *fragPath);
  void createProgram();
};
} // namespace FelicoEngine
