#version 150

out vec4 FragColor;

in vec3 reflectedVector;

uniform samplerCube environmentMap;

void main(void)
{
    vec4 reflectedColour = texture(environmentMap, reflectedVector);
    FragColor = reflectedColour;
}