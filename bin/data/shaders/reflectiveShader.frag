#version 150

out vec4 FragColor;

in vec3 reflectedVector;

uniform samplerCube skybox;

void main(void)
{
    vec4 reflectedColour = texture(skybox, reflectedVector);
    FragColor = reflectedColour;
}