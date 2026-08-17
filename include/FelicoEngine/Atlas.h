#pragma once

#include <FelicoEngine/Texture.h>
#include <string>
#include <unordered_map>

namespace FelicoEngine {
struct AtlasRect {
  float x;
  float y;
  float w;
  float h;
};

class Atlas {
public:
  Atlas(const char *texturePath);
  Atlas(const char *texturePath, int cols, int rows);
  const Texture &getTexture() const;
  AtlasRect getRegion(const char *name) const;
  AtlasRect getFrame(int index) const;
  void createRegion(const char *name, AtlasRect region);

private:
  int m_Cols{0};
  int m_Rows{0};
  Texture m_AtlasTexture;
  std::unordered_map<std::string, AtlasRect> m_Regions;
};
} // namespace FelicoEngine
