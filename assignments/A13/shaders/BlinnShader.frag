#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragUV;

layout(location = 0) out vec4 outColor;


layout(binding = 1) uniform sampler2D tex;

layout(binding = 2) uniform GlobalUniformBufferObject {
	vec3 lightPos;	// position of the spotlight
	vec3 lightDir;	// direction of the spotlight
	vec4 lightColor;// color of the spotlight	
	vec3 eyePos;	// position of the viewer
} gubo;

layout(binding = 3) uniform sampler2D texEmit;

const float beta = 2.0f;	// decay exponent of the spotlight
const float g = 3;			// target distance of the spotlight
const float cosout = 0.5;	// cosine of the outer angle of the spotlight
const float cosin  = 0.95;	// cosine of the inner angle of the spotlight

const float gamma = 160.0f;	// cosine power for the Blinn specular reflection

// coefficients for the spehrical harmonics ambient light term
const vec3 C00  = vec3( .38f, .43f, .45f)/8.0f;
const vec3 C1m1 = vec3( .29f, .36f, .41f)/8.0f;
const vec3 C10  = vec3( .04f, .03f, .01f)/8.0f;
const vec3 C11  = vec3(-.10f,-.10f,-.09f)/8.0f;
const vec3 C2m2 = vec3(-.06f,-.06f,-.04f)/8.0f;
const vec3 C2m1 = vec3( .01f,-.01f,-.05f)/8.0f;
const vec3 C20  = vec3(-.09f,-.13f,-.15f)/8.0f;
const vec3 C21  = vec3(-.06f,-.05f,-.04f)/8.0f;
const vec3 C22  = vec3( .02f, .00f,-.05f)/8.0f;
//BRDF function for the Lambert + Blinn diffusion and specular model
vec3 BRDF(vec3 V, vec3 N, vec3 L, vec3 Md, vec3 Ms, float gamma) {
	//vec3 V  - direction of the viewer
	//vec3 N  - normal vector to the surface
	//vec3 L  - light vector (from the light model)
	//vec3 Md - main color of the surface
	//vec3 Ms - specular color of the surface
	//float gamma - Exponent for power specular term
	vec3 Lambert = Md*max(dot(L,N),0.0);
	vec3 omega_r = normalize(V);
	vec3 half_vector = normalize(L+omega_r);
	vec3 Blinn = Ms*pow(clamp(dot(N,half_vector),0.0,1.0),gamma);
	vec3 Lambert_Blinn = Lambert + Blinn;
	return Lambert_Blinn;
}

void main() {

	vec3 N = normalize(fragNorm);				// surface normal
	vec3 V = normalize(gubo.eyePos - fragPos);	// viewer direction
	vec3 MD = texture(tex, fragUV).rgb;			// diffuse color
	vec3 MA = MD;								// ambient color
	vec3 MS = vec3(1);							// specular color
	vec3 ME = texture(texEmit, fragUV).rgb;		// emission color

	vec3 lightDir = gubo.lightDir;
	vec3 lightColor = clamp((dot(normalize(gubo.lightPos-fragPos),gubo.lightDir)-cosout)/(cosin-cosout),0.0,1.0)*
	pow(g/length(gubo.lightPos-fragPos),beta)*
	gubo.lightColor.rgb;

	vec3 L = gubo.lightDir;
	// Write the shader here
	vec3 DiffSpec = BRDF(V, N, L, MD, MS, gamma);
	vec3 Ambient = C00+ N.x*C11+
	N.y*C1m1+
	N.z*C10+
	N.x*N.y*C2m2+
	N.y*N.z*C2m1+
	N.z*N.x*C21+
	(pow(N.x,2)-pow(N.y,2))*C22+
	3*pow(N.z,2)*C20;

	outColor =vec4(DiffSpec * lightColor + MA*Ambient+ ME, 1.0f);;	// output color
}
