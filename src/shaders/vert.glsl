#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 u_projection;

out vec2 texCoord;
out vec3 color;

void main(){
    texCoord = aTexCoord;
    gl_Position = u_projection * vec4(aPos, 0.0, 1.0);
    color = aColor;
}
