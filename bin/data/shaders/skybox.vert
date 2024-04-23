#version 150

in vec3 position;

out vec3 texCoord;

uniform mat4 modelViewProjectionMatrix;

void main() {
    texCoord = position;
    gl_Position = modelViewProjectionMatrix * vec4(position, 1.0);
}
