#pragma once

#include <glm/vec2.hpp>

namespace FelicoEngine {
enum class Anchor {
  TopLeft,
  TopCenter,
  TopRight,
  MiddleLeft,
  Center,
  MiddleRight,
  BottomLeft,
  BottomCenter,
  BottomRight
};

struct Transform {
  glm::vec2 position{0.0f};
  glm::vec2 scale{1.0f};
  float rotation{0.0f};
  Anchor anchor{Anchor::Center};
  glm::vec2 getAnchor() {
    switch (anchor) {
    case Anchor::TopLeft:
      return {0, 0};
      break;
    case Anchor::TopCenter:
      return {-0.5, 0};
      break;
    case Anchor::TopRight:
      return {-1, 0};
      break;
    case Anchor::MiddleLeft:
      return {0, -0.5};
      break;
    case Anchor::Center:
      return {-0.5, -0.5};
      break;
    case Anchor::MiddleRight:
      return {-1, -0.5};
      break;
    case Anchor::BottomLeft:
      return {0, -1};
      break;
    case Anchor::BottomCenter:
      return {-0.5, -1};
      break;
    case Anchor::BottomRight:
      return {-1, -1};
      break;
    default:
      return {-0.5, -0.5};
      break;
    }
  }
};
} // namespace FelicoEngine
