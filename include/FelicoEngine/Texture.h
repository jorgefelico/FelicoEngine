#pragma once

namespace FelicoEngine {
class Texture {
public:
  Texture(const char *path);
  ~Texture();
  void bind(unsigned int slot = 0) const;
  int width() const;
  int height() const;

private:
  unsigned int m_ID{0};
  int m_Width{0};
  int m_Height{0};
};
} // namespace FelicoEngine
