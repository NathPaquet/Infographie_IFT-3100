OF_GLSL_SHADER_HEADER


// -- output to frag shader ------------- //
// ------------------------------ //

// attributs de sommet
in vec4 position;
in vec4 normal;
in vec2 texcoord;

// attributs en sortie
out vec3 surface_position;
out vec3 surface_normal;
out vec2 surface_texcoord;

//-- set automatically by OF ---------//
// these are passed in from OF programmable renderer
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat4 textureMatrix;
uniform vec4 globalColor;
uniform mat4 normalMatrix;

uniform float usingTexture;
uniform float usingColors;

//----------------------------------

uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;
uniform sampler2D texture_displacement;
uniform float matDisplacementStrength;

vec2 textureRepeatTimes = vec2(1.0, 1.0);
float displaceBias = 0.5;

vec4 apply_displacement(vec2 textureCoords){
	vec4 displacement = texture(texture_displacement, textureCoords);
	vec4 newVertexPos = vec4(normal.xyz * (displacement.r * matDisplacementStrength - displaceBias), 0.0);
	newVertexPos += position;
	
   return newVertexPos;
}

void main (void){
	vec2 newTexcoord = mod(texcoord * textureRepeatTimes, 1.0);
	newTexcoord = texcoord * textureRepeatTimes;
	vec4 newVertexPos = apply_displacement(newTexcoord);
	
	surface_position = vec3(modelViewMatrix * newVertexPos);

	surface_normal = normalize(vec3(normalMatrix * normal));
	
	surface_texcoord = newTexcoord;
	
	gl_Position = modelViewProjectionMatrix * newVertexPos;
	
}