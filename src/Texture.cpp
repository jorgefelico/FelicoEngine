#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "glad/glad.h"
#include "stb_image.h"

namespace FelicoEngine {
Texture::Texture(const char *path) {
  stbi_set_flip_vertically_on_load(1);
  int width, height, channels;
  unsigned char *data = stbi_load(path, &width, &height, &channels, 0);
  if (!data)
    return;
  glGenTextures(1, &m_ID);
  glBindTexture(GL_TEXTURE_2D, m_ID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, data);
  stbi_image_free(data);
}

Texture::~Texture() { glDeleteTextures(1, &m_ID); }

void Texture::bind(unsigned int slot) const {
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, m_ID);
}
} // namespace FelicoEngine
