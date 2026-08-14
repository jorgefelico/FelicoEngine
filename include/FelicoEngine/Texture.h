#pragma once

namespace FelicoEngine {
class Texture {
public:
  Texture(const char *path);
  ~Texture();
  void bind(unsigned int slot = 0) const;

private:
  unsigned int m_ID;
};
} // namespace FelicoEngine
