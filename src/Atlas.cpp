#include "FelicoEngine/Texture.h"
#include <FelicoEngine/Atlas.h>
#include <cstdio>

namespace FelicoEngine {
Atlas::Atlas(const char *texturePath) : m_AtlasTexture(texturePath) {};
Atlas::Atlas(const char *texturePath, int cols, int rows)
    : m_Cols(cols), m_Rows(rows), m_AtlasTexture(texturePath) {};

const Texture &Atlas::getTexture() const { return m_AtlasTexture; };

void Atlas::createRegion(const char *name, AtlasRect region) {
  m_Regions[name] = region;
};

AtlasRect Atlas::getRegion(const char *name) const {
  auto it = m_Regions.find(name);
  if (it == m_Regions.end()) {
    printf("Could not find region %s\n", name);
    return AtlasRect{0.0f, 0.0f, 0.0f, 0.0f};
  }
  return it->second;
};

AtlasRect Atlas::getFrame(int index) const {
  if (m_Rows == 0 || m_Cols == 0) {
    printf("Atlas is not a grid\n");
    return AtlasRect{0.0f, 0.0f, 0.0f, 0.0f};
  }
  if (index < 0 || index >= m_Cols * m_Rows) {
    printf("Frame index out of bounds\n");
    return AtlasRect{0.0f, 0.0f, 0.0f, 0.0f};
  }

  float colWidth = (float)m_AtlasTexture.width() / (float)m_Cols;
  float rowHeight = (float)m_AtlasTexture.height() / (float)m_Rows;
  int column = index % m_Cols;
  int row = index / m_Cols;
  float x = column * colWidth;
  float y = row * rowHeight;
  return AtlasRect{x, y, colWidth, rowHeight};
};
} // namespace FelicoEngine
