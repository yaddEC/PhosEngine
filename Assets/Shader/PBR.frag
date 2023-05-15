#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 FragPos;
in mat3 TBN;
in vec4 FragPosPoint[6];
in vec4 FragPosSpot[6];
in vec4 FragPosDir[3];

uniform vec3 viewPos;
uniform int lenghtDirLight;
uniform int lenghtPointLight;
uniform int lenghtSpotLight;


struct ColorMap 
{
    vec3 color;
    sampler2D texture;
    bool useTexture;
};

struct Material
{ 
    // ColorMap specular;
    ColorMap albedo;
    ColorMap metallic;
    ColorMap roughness;
    ColorMap normalMap;
};

uniform Material material;


// Lights Structs
// Directional 
struct DirLight {
    vec3 direction;

    vec3 color;
    float intensity;
    sampler2D shadowMap;
};  
#define MAX_DIR_LIGHTS 3
uniform DirLight dirLights[MAX_DIR_LIGHTS];

// Point Light
struct PointLight {
    vec3 position;

    vec3 color;
    float intensity;

    float constant;
    float linear;
    float quadratic;
};
#define MAX_POINT_LIGHTS 6
uniform PointLight pointLights[MAX_POINT_LIGHTS];

// Spot Light
struct SpotLight {
    vec3  position;
    vec3  direction;

    float cutOff;
    float outerCutOff;

    vec3 color;
    float intensity;

    float constant;
    float linear;
    float quadratic;

    sampler2D shadowMap;
}; 
#define MAX_SPOT_LIGHTS 6
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];


const float PI = 3.14159265359;
//Function

// ----------------------------------------------------------------------------
vec3 GetColorMapColor(ColorMap map)
{
    if(map.useTexture)
    {
        return texture(map.texture, texCoord).xyz;
    }
    else
    {
        return map.color;
    }
}
// ----------------------------------------------------------------------------
vec3 getNormalFromMap()
{
    // vec3 tangentNormal = GetColorMapColor(material.normalMap) * 2.0 - 1.0;

    // vec3 Q1  = dFdx(FragPos);
    // vec3 Q2  = dFdy(FragPos);
    // vec2 st1 = dFdx(texCoord);
    // vec2 st2 = dFdy(texCoord);

    // vec3 N   = normalize(Normal);
    // vec3 T  = normalize(Q1 * st2.t - Q2 * st1.t);
    // vec3 B  = -normalize(cross(N, T));
    // mat3 TBN = mat3(T, B, N);

    // return normalize(TBN * tangentNormal);
    return vec3(0);
}
// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}
// ----------------------------------------------------------------------------
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 F0, float metallic, float roughness, vec3 albedo)
{
    // calculate per-light radiance
    vec3 L = normalize(-light.direction);
    vec3 H = normalize(viewDir -light.direction);
    vec3 radiance = light.color * light.intensity;

    // Cook-Torrance BRDF
    float NDF = DistributionGGX(normal, H, roughness);   
    float G   = GeometrySmith(normal, viewDir, L, roughness);      
    vec3  F   = fresnelSchlick(max(dot(H, viewDir), 0.0), F0);
        
    vec3 numerator    = NDF * G * F;
    float denominator = 4.0 * max(dot(normal, viewDir), 0.0) * max(dot(normal, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
    vec3 specular = (numerator / denominator) * light.intensity ;

    // kS is equal to Fresnel
    vec3 kS = F;
    // for energy conservation, the diffuse and specular light can't
    // be above 1.0 (unless the surface emits light); to preserve this
    // relationship the diffuse component (kD) should equal 1.0 - kS.
    vec3 kD = vec3(1.0) - kS;
    // multiply kD by the inverse metalness such that only non-metals 
    // have diffuse lighting, or a linear blend if partly metal (pure metals
    // have no diffuse light).
    kD *= 1.0 - metallic;

    // scale light by NdotL
    float NdotL = max(dot(normal, L), 0.0);
    return (kD * albedo / PI + specular) * radiance * NdotL;
}
// ----------------------------------------------------------------------------
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 F0, float metallic, float roughness, vec3 albedo)
{
    // calculate per-light radiance
    vec3 lightDir = normalize(light.position - FragPos);
    vec3 H = normalize(viewDir + lightDir);
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / ((light.quadratic * distance * distance)
                            + (light .linear * distance) 
                            + (light.constant));
    vec3 radiance = light.color * attenuation * light.intensity;

    // Cook-Torrance BRDF
    float NDF = DistributionGGX(normal, H, roughness);   
    float G   = GeometrySmith(normal, viewDir, lightDir, roughness);      
    vec3  F   = fresnelSchlick(max(dot(H, viewDir), 0.0), F0);
        
    vec3 numerator    = NDF * G * F;
    float denominator = 4.0 * max(dot(normal, viewDir), 0.0) * max(dot(normal, lightDir), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
    vec3 specular = (numerator / denominator) * light.intensity ;

    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;

    // scale light by NdotL
    float NdotL = max(dot(lightDir, normal), 0.0);

    return (kD * albedo / PI + specular) * radiance * NdotL;
}
// ----------------------------------------------------------------------------
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec3 F0, float metallic, float roughness, vec3 albedo)
{
    // calculate per-light radiance
    vec3 L = normalize(light.position - FragPos);
        
    float theta = dot(L, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // clamp((theta - currentLight.spotOuterCutoff) / epsilon, 0.0, 1.0)
    if(theta / light.outerCutOff > 1)
    {
        vec3 H = normalize(viewDir + L);
        float distance = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant 
                                    + light.linear * distance 
                                    + light.quadratic * (distance * distance));

        vec3 radiance  = light.color * light.intensity * intensity;

        float NDF = DistributionGGX(normal, H, roughness);   
        float G   = GeometrySmith(normal, viewDir, L, roughness);      
        vec3  F   = fresnelSchlick(max(dot(H, viewDir), 0.0), F0);
            
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(normal, viewDir), 0.0) * max(dot(normal, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
        vec3 specular = (numerator / denominator) * light.intensity * intensity;

        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;

        float NdotL = max(dot(normal, L), 0.0);
        return (kD * albedo / PI + specular * attenuation) * radiance * NdotL;
    }
    return vec3(0);
}
// ----------------------------------------------------------------------------



void main ()
{
    vec3 albedo     = pow(GetColorMapColor(material.albedo), vec3(2.2));
    // vec3 albedo     = pow(GetColorMapColor(material.albedo), vec3(1));
    float metallic  = GetColorMapColor(material.metallic).r;
    float roughness = GetColorMapColor(material.roughness).r;

    // Don't have AO 
    float ao        = 1;

    // vec3 N = getNormalFromMap() * -1;
    vec3 normal = GetColorMapColor(material.normalMap); 
    normal = normal * 2.0 - 1.0;   
    normal = normalize(TBN * normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)    
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

    // reflectance equation
    vec3 Lo = vec3(0.0);

    for(int i = 0; i < lenghtDirLight; i++)
    {
        Lo += CalcDirLight(dirLights[i], normal, viewDir, F0, metallic, roughness, albedo);
    }
    for(int i = 0; i < lenghtPointLight; i++)
    {
        Lo += CalcPointLight(pointLights[i], normal, viewDir, F0, metallic, roughness, albedo);
    }
    for(int i = 0; i < lenghtSpotLight; i++)
    {
        Lo += CalcSpotLight(spotLights[i], normal, viewDir, F0, metallic, roughness, albedo);
    }

    
    // ambient lighting (note that the next IBL tutorial will replace 
    // this ambient lighting with environment lighting).
    vec3 ambient = 0.01 * albedo * ao;
    
    vec3 color = ambient + Lo;

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2)); 

    FragColor = vec4(color, 1.0);
}