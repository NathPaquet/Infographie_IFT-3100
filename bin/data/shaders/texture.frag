
OF_GLSL_SHADER_HEADER

// we are going to use 2 lights
// we also have 2 ofLights in ofApp
#define MAX_LIGHTS 2

const float PI = 3.1415926535897932384626433832795;
const float light_attenuation_factor_constant = 0.01;
const float light_attenuation_factor_linear = 0.000001;
const float light_attenuation_factor_quadratic = 0.0000001;

uniform sampler2D mapDiffuse;
uniform sampler2D mapNormal;
uniform sampler2D mapDisplacement;
uniform sampler2D mapAORoughMetal;
uniform sampler2D mapInfluence;

uniform float uIsDrawingInto;

//-- coming in from vertex shader ------//
in vec3 eyePosition;

in vec2 v_texcoord;
in vec3 v_transformedNormal;
in vec3 v_normal;
in vec3 v_eyePosition;
in vec3 v_worldPosition;
in vec4 v_color;

in vec4 mv_positionVarying;
//---------------------------------------


//-- Material uniforms -----------------//
uniform vec4 mat_ambient;
uniform vec4 mat_diffuse;
uniform vec4 mat_specular;
uniform vec4 mat_emissive;
uniform float mat_shininess;
uniform float matMetallic;
uniform float matRoughness;
uniform float matOcclusion;
uniform vec4 global_ambient;
//---------------------------------------

// indice de réfraction de l'effet de Fresnel;
uniform vec3 material_fresnel_ior;

// facteur d'exposition
uniform float tone_mapping_exposure;

// facteur gamma
uniform float tone_mapping_gamma;

// -- copied from libs / openFrameworks / gl / shaders --------------- //
// https://openframeworks.cc/documentation/gl/ofLight%3A%3AData
// set from ofMaterial 
float light_intensity = 1.0;
struct lightData
{
	vec3 ambientColor;

	float enabled;
	vec4 ambient;
	float type; // 0 = pointlight 1 = directionlight
	vec4 position; // where are we
	vec4 diffuse; // how diffuse
	vec4 specular; // what kinda specular stuff we got going on?
				   // attenuation
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	// only for spot
	float spotCutoff;
	float spotCosCutoff;
	float spotExponent;
	// spot and area
	vec3 spotDirection;
	// only for directional
	vec3 halfVector;
	// only for area
	float width;
	float height;
	vec3 right;
	vec3 up;
};

uniform lightData lights[MAX_LIGHTS];


void pointLight( in lightData light, in vec3 normal, in vec3 ecPosition3, inout vec3 ambient, inout vec3 diffuse, inout vec3 specular ){
	float nDotVP;       // normal . light direction
	float nDotHV;       // normal . light half vector
	float pf;           // power factor
	float attenuation;  // computed attenuation factor
	float d;            // distance from surface to light source
	vec3  VP;           // direction from surface to light position
	vec3  halfVector;   // direction of maximum highlights
	vec3 eye = -normalize(v_eyePosition);
	
	// Compute vector from surface to light position
	VP = vec3 (light.position.xyz) - ecPosition3;
	
	// Compute distance between surface and light position
	d = length(VP);
	
	
	// Compute attenuation
	attenuation = 1.0 / (light.constantAttenuation + light.linearAttenuation * d + light.quadraticAttenuation * d * d);
	
	// Normalize the vector from surface to light position
	VP = normalize(VP);
	halfVector = normalize(VP + eye);
	nDotHV = max(0.0, dot(normal, halfVector));
	nDotVP = max(0.0, dot(normal, VP));
	
	ambient += light.ambient.rgb * attenuation;
	diffuse += light.diffuse.rgb * nDotVP * attenuation;
#ifndef TARGET_OPENGLES
#define SPECULAR_REFLECTION
#endif
#ifndef SPECULAR_REFLECTION
	// ha! no branching :)
	pf = mix(0.0, pow(nDotHV, mat_shininess), step(0.0000001, nDotVP));
	specular += light.specular.rgb * pf * nDotVP * attenuation;
#else
	// fresnel factor
	// http://en.wikibooks.org/wiki/GLSL_Programming/Unity/Specular_Highlights_at_Silhouettes
	float w = pow(1.0 - max(0.0, dot(halfVector, VP)), 5.0);
	vec3 specularReflection = attenuation * vec3(light.specular.rgb)
	* mix(vec3(mat_specular.rgb), vec3(1.0), w)
	* pow(nDotHV, mat_shininess);
	specular += mix(vec3(0.0), specularReflection, step(0.0000001, nDotVP));
#endif
}
//--------------------------------------- //

// final color to output
out vec4 FRAGCOLOR;

vec2 textureRepeatTimes = vec2(1.0, 1.0);


//-- normal ------------------------------------ //
// http://www.geeks3d.com/20130122/normal-mapping-without-precomputed-tangent-space-vectors/
// http://www.thetenthplanet.de/archives/1180
mat3 CotangentFrame(vec3 N, vec3 p, vec2 uv) {
	// get edge vectors of the pixel triangle
	vec3 dp1 = dFdx(p);
	vec3 dp2 = dFdy(p);
	vec2 duv1 = dFdx(uv);
	vec2 duv2 = dFdy(uv);
	
	// solve the linear system
	vec3 dp2perp = cross(dp2, N);
	vec3 dp1perp = cross(N, dp1);
	vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
	vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;
	
	// construct a scale-invariant frame
	float invmax = inversesqrt(max(dot(T, T), dot(B, B)));
	return mat3(T * invmax, B * invmax, N);
}

vec3 PerturbNormal(vec3 normalMap, vec3 N, vec3 V, vec2 texcoord) {
	// assume N, the interpolated vertex normal and
	// V, the view vector (vertex to eye)
	vec3 map = normalMap * 255. / 127. - 128. / 127.;
	mat3 TBN = CotangentFrame(N, -V, texcoord);
	return normalize(TBN * map);
}

// fonction de distribution des microfacettes (Trowbridge-Reitz)
float trowbridge_reitz(vec3 n, vec3 h, float roughness)
{
  float a = roughness * roughness;
  float a2 = a * a;
  float ndh = max(dot(n, h), 0.0);
  float ndh2 = ndh * ndh;
  float numerator = a2;
  float denominator = (ndh2 * (a2 - 1.0) + 1.0);
  denominator = denominator * denominator * PI;
  return numerator / denominator;
}



// fonction géométrique pour calculer l'impact de l'occlusion et de l'ombrage des microfacettes (Schlick-Beckmann)
float schlick_beckmann(float costheta, float roughness)
{
  float r = (roughness + 1.0);
  float k = (r * r) / 8.0;
  float numerator = costheta;
  float denominator = costheta * (1.0 - k) + k;
  return numerator / denominator;
}

float smith(vec3 n, vec3 l, vec3 v, float roughness)
{
  float ndl = max(dot(n, l), 0.0);
  float ndv = max(dot(n, v), 0.0);
  float shadow = schlick_beckmann(ndl, roughness);
  float occlusion = schlick_beckmann(ndv, roughness);
  return shadow * occlusion;
}

// fonction qui calcul l'effet de Fresnel
vec3 schlick_fresnel(float costheta, vec3 f0)
{
  return f0 + (1.0 - f0) * pow(1.0 - costheta, 5.0);
}

vec3 brdf_cook_torrance()
{
	// re-normaliser la normale après interpolation
	vec3 n = normalize(v_normal);

	// calculer la direction de la surface vers la caméra (v)
	vec3 v = normalize(-v_eyePosition);

	// échantillonage de la texture diffuse
	vec3 texture_sample_diffuse = texture(mapDiffuse, v_texcoord).rgb;
	texture_sample_diffuse = pow(texture_sample_diffuse, vec3(tone_mapping_gamma));

	// échantillonage de la texture de métallicité
	float texture_sample_metallic = texture(mapAORoughMetal, v_texcoord).b;

	// échantillonage de la texture de rugosité
	float texture_sample_roughness = texture(mapAORoughMetal, v_texcoord).g;

	// échantillonage de la texture d'occlusion
	float texture_sample_occlusion = texture(mapAORoughMetal, v_texcoord).r;

	// facteurs du matériau combinées avec les échantillons de couleur
	float metallic = matMetallic * texture_sample_metallic;
	float roughness = matRoughness * texture_sample_roughness;
	float occlusion = matOcclusion * texture_sample_occlusion;

	// combiner l'échantillon de la texture diffuse avec la couleur diffuse du matériau
	vec3 albedo = mat_diffuse.rgb * texture_sample_diffuse;

	// initialiser la couleur résultante
	vec3 color = vec3(0.0);

	// Loop over each light source
	int num_lights = MAX_LIGHTS;
	for (int i = 0; i < num_lights; ++i) {
		// calculer la direction de la surface vers la lumière (l)
		vec3 l = normalize(lights[i].position.xyz /*light_positions[i]*/ - v_eyePosition);

		// calculer la distance entre la position de la lumière et de la surface
		float light_distance = length(lights[i].position.xyz /*light_positions[i]*/ - v_eyePosition);

		// calculer l'atténuation de l'intensité de la lumière en fonction de la distance
		float light_attenuation = 1.0 / (light_attenuation_factor_constant + 
											light_attenuation_factor_linear * light_distance + 
											light_attenuation_factor_quadratic * (light_distance * light_distance));

		// calculer la radiance de la lumière
		vec3 radiance = lights[i].ambientColor /*TODO*/ * light_attenuation * light_intensity /*lights[i].intensity*/ /*TODO*/;

		// calculer le niveau de réflexion diffuse (n • l)
		float diffuse_reflection = max(dot(n, l), 0.0);

		// calculer la direction du demi-vecteur de réflection (h)
		vec3 h = normalize(l + v);

		// calculer la distribution des microfacettes
		float d = trowbridge_reitz(n, h, roughness);

		// calculer la fonction géométrique
		float g = smith(n, l, v, roughness);

		// reflexion de la surface avec un angle d'incidence nul
		vec3 f0 = material_fresnel_ior;

		// moduler l'effet de Fresnel avec la couleur diffuse en fonction du facteur de métallicité
		f0 = mix(f0, albedo, metallic);

		// calculer l'effet de Fresnel
		vec3 f = schlick_fresnel(max(dot(h, v), 0.0), f0);

		// calculer le numérateur de l'équation (produit des fonctions d, f et g)
		vec3 coor_torrance_numerator = d * f * g;

		// calculer le dénominateur de l'équation (facteur de normalisation)
		float coor_torrance_denominator = 4.0 * max(dot(n, v), 0.0) * diffuse_reflection;

		// calculer le résultat de l'équation avec le numérateur et de dénominateur
		vec3 specular = coor_torrance_numerator / max(coor_torrance_denominator, 0.001);

		// mixer avec la couleur spéculaire du matériau
		specular = specular * mat_specular.rgb;

		// calculer le ratio de réflection de la lumière à partir de l'effet de Fresnel (contribution spéculaire)
		vec3 ks = f;

		// calculer le ratio de réfraction (contribution diffuse) proportionnelement à la contribution spéculaire
		vec3 kd = vec3(1.0) - ks;

		// pondérer la contribution diffuse en fonction du niveau de métallicité de la surface
		kd *= 1.0 - metallic;

		// calculer la réflectance de la fonction BRDF de Cook-Torrance
		vec3 reflectance = (kd * albedo / PI + specular) * radiance * diffuse_reflection;

		// accumuler la contribution de cette lumière
		color += reflectance;
	}

	// retourner la couleur
	return color;
}

//----------------------------------------------------//

void main() {
	vec2 newTexcoord = v_texcoord * textureRepeatTimes;
	
	vec3 mv_normal = normalize(v_transformedNormal);
	vec3 normalMapVec = texture(mapNormal, newTexcoord).xyz;
	vec3 PN = PerturbNormal( normalMapVec, mv_normal, v_eyePosition, newTexcoord);
	
	// float gamma = 2.2;
	
	// vec3 diffuseFromTex = texture(mapDiffuse, newTexcoord).rgb;
	// vec3 diffuseColor = pow(diffuseFromTex, vec3(gamma));
	
	// vec3 baseColor = diffuseColor;
	
	vec3 ambient = global_ambient.rgb;
	vec3 diffuse = vec3(0.0,0.0,0.0);
	vec3 specular = vec3(0.0,0.0,0.0);
	
	vec3 normal = normalize(PN);
	
	// loop through the lights and accumulate output into ambient, diffuse and specular values
	for( int i = 0; i < MAX_LIGHTS; i++ ){
		if(lights[i].enabled<0.5) continue;
		if(lights[i].type<0.5){
			pointLight(lights[i], normal, v_eyePosition, ambient, diffuse, specular);
		}
	}
	
	////////////////////////////////////////////////////////////
	// now add the material info
	// vec4 tex = texture(mapDiffuse, newTexcoord);
	// vec4 localColor = vec4(ambient,1.0) * mat_ambient.a * tex + vec4(diffuse,1.0) * mat_diffuse.a * tex + (vec4(specular,1.0) * mat_specular)*mat_specular.a;
	
	// vec3 color = localColor.rgb;
	// // ambient occlusion values are baked into the r value of the mapAORoughMetal material
	// vec3 aoRoughMetal = texture( mapAORoughMetal, newTexcoord).xyz;
	// color *= (0.35 + aoRoughMetal.r * 0.65);
	
	diffuse = vec3(0.0);
	specular = vec3(0.0);
	// lets recalc light for smooth surface
	for( int i = 0; i < MAX_LIGHTS; i++ ){
		if(lights[i].enabled<0.5) continue;
		if(lights[i].type<0.5){
			pointLight(lights[i], mv_normal, v_eyePosition, ambient, diffuse, specular);
		}
	}
	
	// vec4 bumpColor = texture(mapDisplacement, newTexcoord );
	// vec3 innerColor = mat_emissive.rgb;
	// innerColor = diffuse * innerColor + (specular.rgb * mat_specular.a).rgb;
	// innerColor = innerColor * (1.0-mat_emissive.a) + mat_emissive.rgb * mat_emissive.a;
	
	// vec4 mapInfValue = texture(mapInfluence, newTexcoord);
	
	// color = mix( innerColor, color, pow(mapInfValue.r, 0.5) * pow(clamp(bumpColor.r*2.0, 0.0, 1.0), 0.3) );
	
	// float mixAmnt = mapInfValue.g;
	// color.rgb = mix(color.rgb, vec3(1,1,1), mixAmnt * uIsDrawingInto );

	/*
		Cook-Torrance
	*/
	// évaluation du modèle d'illumination
	vec3 color = brdf_cook_torrance();

	// ajustement de la couleur en fonction du facteur d'exposition
	color = vec3(1.0) - exp(-color * tone_mapping_exposure);

	// mappage tonal de la couleur HDR vers LDR
	// if (tone_mapping_toggle)
	// 	color = tone_mapping_aces_filmic(color);
	// else
	// 	color = tone_mapping_reinhard(color);

	// conversion de couleur de l'espace linéaire vers l'espace gamma
	color = pow(color, vec3(1.0 / tone_mapping_gamma));
	
	FRAGCOLOR = vec4(color, 1.0);
}
