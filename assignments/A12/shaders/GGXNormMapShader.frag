#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec4 fragTan;
layout(location = 3) in vec2 fragUV;

layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform sampler2D tex;
layout(binding = 3) uniform sampler2D normMap;
layout(binding = 4) uniform sampler2D matMap;

layout(binding = 2) uniform GlobalUniformBufferObject {
	vec3 lightDir;
	vec4 lightColor;
	vec3 eyePos;
} gubo;

vec3 BRDF(vec3 V, vec3 N, vec3 L, vec3 Md, float F0, float metallic, float roughness) {
	//vec3 V  - direction of the viewer
	//vec3 N  - normal vector to the surface
	//vec3 L  - light vector (from the light model)
	//vec3 Md - main color of the surface
	//float F0 - Base color for the Fresnel term
	//float metallic - parameter that mixes the diffuse with the specular term.
	//                 in particular, parmeter K seen in the slides is: float K = 1.0f - metallic;
	//float roughness - Material roughness (parmeter rho in the slides).
	//specular color Ms is not passed, and implicitely considered white: vec3 Ms = vec3(1.0f);
	float pi = 3.141592;
	vec3 hlx = normalize(L+V);
	float D = pow(roughness,2)/(pi*pow((pow(clamp(dot(N,hlx),0.0,1.0),2)*(pow(roughness,2)-1)+1),2));
	float F = F0 + (1-F0)*pow((1-clamp(dot(V,hlx),0.0,1.0)),5);
	float G_ggx_omega_r = 2/(1+sqrt(1+pow(roughness,2)*(1-pow(dot(N,V),2))/pow(dot(N,V),2)));
	float G_ggx_L = 2/(1+sqrt(1+pow(roughness,2)*(1-pow(dot(N,L),2))/pow(dot(N,L),2)));
	float G_ggx = G_ggx_omega_r*G_ggx_L;
	vec3 Cook_Torrance_spec = vec3(1.0f)*(D*F*G_ggx/(4*clamp(dot(V,N),0.0,1.0)));
	vec3 Cook_Torrance_diff = Md*clamp(dot(L,N),0.0,1.0);
	vec3 Cook_Torrance = ((1-metallic)*Cook_Torrance_diff)+(metallic*Cook_Torrance_spec); 
	return Cook_Torrance;
}

void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 Tan = normalize(fragTan.xyz - Norm * dot(fragTan.xyz, Norm));
	vec3 Bitan = cross(Norm, Tan) * fragTan.w;
	mat3 tbn = mat3(Tan, Bitan, Norm);
	vec4 nMap = texture(normMap, fragUV);
	vec3 N = normalize(tbn * (nMap.rgb * 2.0 - 1.0));

	vec3 albedo = texture(tex, fragUV).rgb;

	vec4 MRAO = texture(matMap, fragUV);
	float roughness = MRAO.g;
	float ao = MRAO.b;
	float metallic = MRAO.r;
	
	vec3 L = gubo.lightDir;
	vec3 lightColor = gubo.lightColor.rgb;

	vec3 V = normalize(gubo.eyePos - fragPos);

	vec3 DiffSpec = BRDF(V, N, L, albedo, 0.3f, metallic, roughness);
	vec3 Ambient = albedo * 0.05f * ao;
	
	outColor = vec4(clamp(0.95 * DiffSpec * lightColor.rgb + Ambient,0.0,1.0), 1.0f);
}