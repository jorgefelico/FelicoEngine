cmake_minimum_required(VERSION 3.16)
project(FelicoEngine VERSION 0.1.0 LANGUAGES CXX C)

# Force C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate compile_commands.json for IDE support (VS Code, CLion, etc.)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------------------------------------------
# Fetch and Build SDL2 Automatically
# ------------------------------------------------------------------------------
include(FetchContent)

# Disable unnecessary SDL2 options to speed up build time
set(SDL_TEST OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)      # Statically link to avoid managing DLLs
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_PIPEWIRE OFF CACHE BOOL "" FORCE)   # Broken on newer PipeWire headers

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-2.30.12   # Stable release tag
    GIT_SHALLOW    TRUE              # Downloads only the tag history for fast cloning
)

FetchContent_MakeAvailable(SDL2)

# ------------------------------------------------------------------------------
# Dependencies
# ------------------------------------------------------------------------------

find_package(OpenGL REQUIRED)

# ------------------------------------------------------------------------------
# Target Definition
# ------------------------------------------------------------------------------

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/FelicoEngine.cpp
    src/Shader.cpp
    src/Mesh.cpp
    src/Utils.cpp
    src/Texture.cpp
    vendor/glad/src/glad.c
  )
    
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb 
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm 
)

# Link SDL2 and OpenGL
target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    $<IF:$<TARGET_EXISTS:SDL2::SDL2-static>,SDL2::SDL2-static,SDL2::SDL2>
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
)

# ------------------------------------------------------------------------------
# Compiler Flags
# ------------------------------------------------------------------------------

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()
