#define STB_IMAGE_IMPLEMENTATION
#include <FelicoEngine/Texture.h>
#include "glad/glad.h"
#include "stb_image.h"

namespace FelicoEngine {
Texture::Texture(const char *path) {
  stbi_set_flip_vertically_on_load(1);
  int width, height, channels;
  unsigned char *data = stbi_load(path, &width, &height, &channels, 4);
  if (!data)
    return;
  glGenTextures(1, &m_ID);
  glBindTexture(GL_TEXTURE_2D, m_ID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);
}

Texture::~Texture() { glDeleteTextures(1, &m_ID); }

void Texture::bind(unsigned int slot) const {
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, m_ID);
}
} // namespace FelicoEngine
