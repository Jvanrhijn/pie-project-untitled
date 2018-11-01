#version 330 core

uniform mat4 MVP;
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vCol;
layout (location = 2) in vec2 vTex;

out vec3 Color;
out vec2 TexCoord;

void main() {
    gl_Position = MVP * vec4(vPos, 1.0);
    Color = vCol;
    TexCoord = vTex;
}
