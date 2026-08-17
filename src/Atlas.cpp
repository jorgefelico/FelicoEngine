#include "FelicoEngine/Texture.h"
#include "nlohmann/json_fwd.hpp"
#include <FelicoEngine/Atlas.h>
#include <FelicoEngine/Utils.h>
#include <cstdio>
#include <nlohmann/json.hpp>

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

void Atlas::loadRegions(const char *jsonPath) {
  std::string content = Utils::readFile(jsonPath);
  try {
    nlohmann::json j = nlohmann::json::parse(content);
    for (auto it = j.begin(); it != j.end(); ++it) {
      const auto &entry = it.value();
      if (entry.contains("rotated") && entry["rotated"].get<bool>()) {
        printf("Region %s is rotated; not supported\n", it.key().c_str());
      }
      const auto &frame = entry["frame"];
      createRegion(it.key().c_str(),
                   AtlasRect{frame["x"].get<float>(), frame["y"].get<float>(),
                             frame["w"].get<float>(), frame["h"].get<float>()});
    }
  } catch (const nlohmann::json::exception &e) {
    printf("Could not parse regions file %s: %s\n", jsonPath, e.what());
  }
};
} // namespace FelicoEngine
