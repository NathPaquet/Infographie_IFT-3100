#version 150

out vec4 fragColor;

in vec3 refractedVector;

uniform samplerCube environmentMap;

void main(void)
{
	vec4 refractedColour = texture(environmentMap, refractedVector);

	fragColor = refractedColour;

}