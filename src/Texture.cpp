#define STB_IMAGE_IMPLEMENTATION
#include "glad/glad.h"
#include "stb_image.h"
#include <FelicoEngine/Texture.h>

namespace FelicoEngine {
Texture::Texture(const char *path) {
  stbi_set_flip_vertically_on_load(1);
  int channels;
  unsigned char *data = stbi_load(path, &m_Width, &m_Height, &channels, 4);
  if (!data) {
    printf("Could not load texture %s: %s\n", path, stbi_failure_reason());
    return;
  }
  glGenTextures(1, &m_ID);
  glBindTexture(GL_TEXTURE_2D, m_ID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);
}

Texture::~Texture() { glDeleteTextures(1, &m_ID); }

void Texture::bind(unsigned int slot) const {
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, m_ID);
}

int Texture::width() const { return m_Width; }

int Texture::height() const { return m_Height; }
} // namespace FelicoEngine
