#include "FelicoEngine.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "glad/glad.h"

namespace FelicoEngine {
FelicoEngine::FelicoEngine(const char *title, unsigned int width,
                           unsigned int height) {
  m_Title = title;
  m_Width = width;
  m_Height = height;
}

void FelicoEngine::init() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Error initializing SDL: %s\n", SDL_GetError());
    return;
  }
  printf("SDL Initialized\n");

  m_Window = SDL_CreateWindow(m_Title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, m_Width, m_Height,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  if (!m_Window) {
    printf("Error creating window: %s\n", SDL_GetError());
    return;
  }

  m_Context = SDL_GL_CreateContext(m_Window);
  if (!m_Context) {
    printf("Error creating GL context: %s\n", SDL_GetError());
    return;
  }

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    return;
  }
}

void FelicoEngine::run() {
  bool shouldClose = false;

  Shader shader("src/shaders/vert.glsl", "src/shaders/frag.glsl");
  float quad[] = {
      // pos       color           UV
      -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom-left
      0.5f,  -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // bottom-right
      0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // top-right
      -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom-left (tri 2)
      0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // top-right
      -0.5f, 0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // top-left

  };
  Mesh mesh(quad, sizeof(quad) / sizeof(quad[0]));
  Texture texture("src/textures/texture_01.png");
  texture.bind(0);
  while (!shouldClose) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        shouldClose = true;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    shader.use();
    mesh.draw();
    SDL_GL_SwapWindow(m_Window);
  }
}

void FelicoEngine::shutdown() {
  SDL_GL_DeleteContext(m_Context);
  SDL_DestroyWindow(m_Window);
  SDL_Quit();
}

FelicoEngine::~FelicoEngine() {}
} // namespace FelicoEngine
