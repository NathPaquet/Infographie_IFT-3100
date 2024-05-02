// IFT3100H24 ~ pbr_330_fs.glsl

#version 330

#define MAX_LIGHTS 6

const float PI = 3.1415926535897932384626433832795;

// attributs de surface interpolés à partir des valeurs en sortie du shader de sommet
in vec3 surface_position;
in vec3 surface_normal;
in vec2 surface_texcoord;

// attribut en sortie
out vec4 fragment_color;

uniform vec3 material_color_ambient;
uniform vec3 material_color_diffuse;
uniform vec3 material_color_specular;
uniform float material_brightness;
uniform float material_metallic;
uniform float material_roughness;
uniform float material_occlusion;
uniform vec3 material_fresnel_ior;

uniform float tone_mapping_exposure;
uniform float tone_mapping_gamma;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_AORoughMetal;
uniform sampler2D texture_normal;

// intensité de la source de lumière
uniform float light_intensity;

struct lightData {
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

// fonction de distribution des microfacettes (Trowbridge-Reitz)
float trowbridge_reitz(vec3 n, vec3 h, float roughness) {
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
float schlick_beckmann(float costheta, float roughness) {
  float r = (roughness + 1.0);
  float k = (r * r) / 8.0;
  float numerator = costheta;
  float denominator = costheta * (1.0 - k) + k;
  return numerator / denominator;
}

// fonction géométrique avec occlusion et ombrage combinés (méthode de Smith)
float smith(vec3 n, vec3 l, vec3 v, float roughness) {
  float ndl = max(dot(n, l), 0.0);
  float ndv = max(dot(n, v), 0.0);
  float shadow = schlick_beckmann(ndl, roughness);
  float occlusion = schlick_beckmann(ndv, roughness);
  return shadow * occlusion;
}

// fonction qui calcul l'effet de Fresnel
vec3 schlick_fresnel(float costheta, vec3 f0) {
  return f0 + (1.0 - f0) * pow(1.0 - costheta, 5.0);
}


vec3 compute_reflectance(in vec3 light_color, in float attenuation, in float light_intensity, in vec3 normal, in vec3 l, in vec3 v, in vec3 h, in vec3 albedo, in float roughness, in float metallic){
  // calculer la radiance de la lumière
  vec3 radiance = light_color * attenuation * light_intensity;

  // calculer le niveau de réflexion diffuse (n • l)
  float diffuse_reflection = max(dot(normal, l), 0.0);

  // calculer la distribution des microfacettes
  float d = trowbridge_reitz(normal, h, roughness);

  // calculer la fonction géométrique
  float g = smith(normal, l, v, roughness);

  // reflexion de la surface avec un angle d'incidence nul
  vec3 f0 = material_fresnel_ior;

  // moduler l'effet de Fresnel avec la couleur diffuse en fonction du facteur de métallicité
  f0 = mix(f0, albedo, metallic);

  // calculer l'effet de Fresnel
  vec3 f = schlick_fresnel(max(dot(h, v), 0.0), f0);

  // calculer le numérateur de l'équation (produit des fonctions d, f et g)
  vec3 coor_torrance_numerator = d * f * g;

  // calculer le dénominateur de l'équation (facteur de normalisation)
  float w_i = max(dot(normal, l), 0.0);

  float coor_torrance_denominator = 4.0 * max(dot(normal, v), 0.0) * w_i;

  // calculer le résultat de l'équation avec le numérateur et de dénominateur
  vec3 specular = coor_torrance_numerator / max(coor_torrance_denominator, 0.001);

  // mixer avec la couleur spéculaire du matériau
  specular = specular * material_color_specular;

  // calculer le ratio de réflection de la lumière à partir de l'effet de Fresnel (contribution spéculaire)
  vec3 ks = f;

  // calculer le ratio de réfraction (contribution diffuse) proportionnelement à la contribution spéculaire
  vec3 kd = vec3(1.0) - ks;

  // pondérer la contribution diffuse en fonction du niveau de métallicité de la surface
  kd *= 1.0 - metallic;

  // calculer la réflectance de la fonction BRDF de Cook-Torrance
  vec3 reflectance = (kd * albedo / PI + specular) * radiance * w_i;

  return reflectance;
}

// Point light
vec3 pointLight( in lightData light, in vec3 normal, in vec3 surface_position, in float roughness, in float metallic, in vec3 albedo){
	float attenuation;  // computed attenuation factor
	vec3  l = vec3 (light.position.xyz) - surface_position; // direction from surface to light position
	float light_distance = length(l);            // distance from surface to light source
	l = normalize(l);
	vec3 v = -normalize(surface_position);
	vec3 h = normalize(l + v);   // direction of maximum highlights
	
	// Compute attenuation
	attenuation = 1.0 / (light.constantAttenuation + light.linearAttenuation * light_distance + light.quadraticAttenuation * (light_distance * light_distance));
	
	return compute_reflectance(light.diffuse.rgb, attenuation, light_intensity, normal, l, v, h, albedo, roughness, metallic);
}

// Directional light
vec3 directionalLight( in lightData light, in vec3 normal, in vec3 surface_position, in float roughness, in float metallic, in vec3 albedo){
	  float d = max(0.0, dot(normal, normalize(vec3(light.position))));

    vec3 l = vec3 (light.position.xyz) - surface_position; // direction from surface to light position
	  vec3 v = -normalize(surface_position);
	  l = normalize(l);
    vec3 h = normalize(l + v);

    vec3 reflectance = compute_reflectance(light.diffuse.rgb, 1.0, light_intensity, normal, l, v, h, albedo, roughness, metallic);
    return reflectance * d;
}

// Spot light
vec3 spotLight( in lightData light, in vec3 normal, in vec3 surface_position, in vec3 albedo, in float roughness, in float metallic){
	float light_distance;            // distance from surface to light source
	vec3  l = light.position.xyz - surface_position;           // direction from surface to light position
	vec3  v = -normalize(surface_position);
	float spotEffect;
	float attenuation;
	vec3  h;   // direction of maximum highlights
	// Compute vector from surface to light position
	spotEffect = max(dot(light.spotDirection, -normalize(l)), 0.0);

	if (spotEffect > light.spotCosCutoff) {
		// Compute distance between surface and light position
		light_distance = length(l);
    attenuation = pow(spotEffect, light.spotExponent) / (light.constantAttenuation + light.linearAttenuation * light_distance + light.quadraticAttenuation * (light_distance * light_distance));

		l = normalize(l);
		h = normalize(l + v);

    return compute_reflectance(light.diffuse.rgb, attenuation, light_intensity, normal, l, v, h, albedo, roughness, metallic);
	}

  return vec3(0.0);
}

mat3 cotangent_frame(vec3 N, vec3 p, vec2 uv){
    // get edge vectors of the pixel triangle
    vec3 dp1 = dFdx( p );
    vec3 dp2 = dFdy( p );
    vec2 duv1 = dFdx( uv );
    vec2 duv2 = dFdy( uv );
 
    // solve the linear system
    vec3 dp2perp = cross( dp2, N );
    vec3 dp1perp = cross( N, dp1 );
    vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
    vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;
 
    // construct a scale-invariant frame 
    float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
    return mat3( T * invmax, B * invmax, N );
}

vec3 perturb_normal( vec3 N, vec3 V, vec2 texcoord ){
   // assume N, the interpolated vertex normal and 
   // V, the view vector (vertex to eye)
   vec3 map = texture(texture_normal, texcoord).xyz;
   map = map * 255./127. - 128./127.;
   mat3 TBN = cotangent_frame(N, -V, texcoord);
   return normalize(TBN * map);
}

//--------------------------------------- //

// mappage tonal de la couleur HDR vers LDR (Reinhard tone mapping)
vec3 tone_mapping_reinhard(vec3 x) {
  return x / (x + vec3(1.0));
}

// mappage tonal de la couleur HDR vers LDR (approximation de la courbe du ACES filmic tone mapping)
vec3 tone_mapping_aces_filmic(vec3 x) {
  float a = 2.51f;
  float b = 0.03f;
  float c = 2.43f;
  float d = 0.59f;
  float e = 0.14f;
  return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);
}

// fonction qui calcule un modèle d'illumination de type pbr avec brdf de cook-torrance
vec3 brdf_cook_torrance() {
  // re-normaliser la normale après interpolation
  vec3 n = normalize(surface_normal);

  // calculer la direction de la surface vers la caméra (v)
  vec3 v = normalize(-surface_position);
  
  vec3 new_normal = perturb_normal(n, v, surface_texcoord);

  // échantillonage de la texture diffuse
  vec3 texture_sample_diffuse = texture(texture_diffuse, surface_texcoord).rgb;

  // conversion de l'échantillon de la texture diffuse de l'espace gamma vers l'espace linéaire
  texture_sample_diffuse = pow(texture_sample_diffuse, vec3(tone_mapping_gamma));

  // échantillonage de la texture de métallicité
  float texture_sample_metallic = texture(texture_AORoughMetal, surface_texcoord).b;

  // échantillonage de la texture de rugosité
  float texture_sample_roughness = texture(texture_AORoughMetal, surface_texcoord).g;

  // échantillonage de la texture d'occlusion
  float texture_sample_occlusion = texture(texture_AORoughMetal, surface_texcoord).r;

  // facteurs du matériau combinées avec les échantillons de couleur
  float metallic = material_metallic * texture_sample_metallic;
  float roughness = material_roughness * texture_sample_roughness;
  float occlusion = material_occlusion * texture_sample_occlusion;

  // combiner l'échantillon de la texture diffuse avec la couleur diffuse du matériau
  vec3 albedo = material_color_diffuse * texture_sample_diffuse;

  // calculer la réflexion ambiante
  vec3 ambient = material_color_ambient * albedo * occlusion;

  // Normal mapping
  vec2 textureRepeatTimes = vec2(1.0, 1.0);
	vec2 newTexcoord = surface_texcoord * textureRepeatTimes;

	vec3 PN = perturb_normal(surface_normal, surface_position, newTexcoord);
	vec3 normal = normalize(PN);
  // Normal mapping
  
  vec3 reflectance_result = vec3(0.0);
  for (int i = 0; i < MAX_LIGHTS; i++){
    if(lights[i].enabled<0.5) continue;
		if(lights[i].type<0.5) {
			reflectance_result += pointLight(lights[i], normal, surface_position, roughness, metallic, albedo);
		} else if (lights[i].type<1.5){
			reflectance_result += directionalLight(lights[i], normal, surface_position, roughness, metallic, albedo);
		} else if (lights[i].type<2.5){
			reflectance_result += spotLight(lights[i], normal, surface_position, albedo, roughness, metallic);
		}
  }

  // mixer la couleur des composantes de réflexion
  vec3 color = (ambient + reflectance_result) * material_brightness;

  // retourner la couleur
  return color;
}

void main()
{
  // évaluation du modèle d'illumination
  vec3 color = brdf_cook_torrance();

  // ajustement de la couleur en fonction du facteur d'exposition
  color = vec3(1.0) - exp(-color * tone_mapping_exposure);

  // mappage tonal de la couleur HDR vers LDR
  // if (tone_mapping_toggle)
  //   color = tone_mapping_aces_filmic(color);
  // else
    
  color = tone_mapping_reinhard(color);

  // conversion de couleur de l'espace linéaire vers l'espace gamma
  color = pow(color, vec3(1.0 / tone_mapping_gamma));

  // assigner la couleur final du fragment dans un attribut en sortie
  fragment_color = vec4(color, 1.0);
}