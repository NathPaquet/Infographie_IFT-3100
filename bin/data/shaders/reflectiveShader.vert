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
	vec4 worldPos = modelMatrix * vec4(position, 1.0);
	vec3 worldPosition = worldPos.xyz;
    gl_Position = projectionMatrix * viewMatrix * worldPos;
	
	vec3 unitNormal = normalize(normal);
	vec3 viewVector = normalize(worldPosition - cameraPosition);

	reflectedVector = reflect(viewVector, unitNormal);
}