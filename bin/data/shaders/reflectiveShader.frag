#version 150

out vec4 FragColor;

in vec3 worldPosition;
in vec3 worldNormal;
in vec3 viewVector;
in vec3 reflectedVector;
in vec3 refractedVector;

uniform samplerCube skybox;

void main(void)
{
    vec4 reflectedColour = texture(skybox, reflectedVector);
    vec4 refractedColour = texture(skybox, refractedVector);
    vec4 enviroColour = mix(refractedColour, reflectedColour, 0.5);

    FragColor = enviroColour;
}