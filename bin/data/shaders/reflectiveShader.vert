#version 150

in vec3 position;
in vec3 normal;

out vec3 worldPosition;
out vec3 worldNormal;
out vec3 viewVector;
out vec3 reflectedVector;
out vec3 refractedVector;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform vec3 cameraPosition;

void main(void)
{
	vec4 worldPos = modelMatrix * vec4(position, 1.0);
	worldPosition = worldPos.xyz;
	worldNormal = normalize(mat3(transpose(inverse(modelMatrix))) * normal);
    viewVector = normalize(cameraPosition - worldPosition);
    gl_Position = projectionMatrix * viewMatrix * worldPos;
	
	vec3 unitNormal = normalize(normal);
	
	reflectedVector = reflect(viewVector, worldNormal);
    refractedVector = refract(viewVector, worldNormal, 1.0 / 1.1);
}