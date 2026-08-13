#version 330 core
in vec3 color;
in vec2 texCoord;

uniform sampler2D u_texture;

out vec4 fragColor;

void main() {
    fragColor = texture(u_texture, texCoord);
}
