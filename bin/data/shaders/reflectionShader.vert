#version 150

in vec3 position;
in vec3 normal;

out vec3 reflectedVector;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform vec3 cameraPosition;

void main(void)
{
	vec4 worldPosition = modelMatrix * vec4(position, 1.0);
    gl_Position = projectionMatrix * viewMatrix * worldPosition;
	
	vec3 unitNormal = normalize(normal);
	vec3 viewVector = normalize(worldPosition.xyz - cameraPosition);

	reflectedVector = reflect(viewVector, unitNormal);
}