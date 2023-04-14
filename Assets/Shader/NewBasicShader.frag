#version 330 core
out vec4 FragColor;

in vec2 texCoord;
// in vec3 Normal;
in vec3 FragPos;
// in vec3 viewPosition;
in mat3 TBN;

in vec3 TangentViewPos;
vec3 TangentFragPos;

// uniform vec3 viewPos;
uniform vec3 ambientColor;
uniform int lenghtDirLight;
uniform int lenghtPointLight;
uniform int lenghtSpotLight;



// Structs

struct DirLight {
    vec3 direction;

    vec3 color;
    float intensity;
};  
#define MAX_DIR_LIGHTS 3
uniform DirLight dirLights[MAX_DIR_LIGHTS];

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
}; 
#define MAX_SPOT_LIGHTS 6
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

struct ColorMap {

    vec3 color;
    sampler2D texture;
    bool useTexture;
};

struct Material{ 
    
    ColorMap specular;
    ColorMap albedo;
    float shininess;
    ColorMap normalMap;
};

uniform Material material;

// Fuctions

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

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 tangentLightPos = TBN * (FragPos - light.direction);
    vec3 lightDir = normalize(tangentLightPos - TangentFragPos);

    float diff = dot(normal, lightDir);
    vec3 diffuse = light.color * light.intensity * diff;

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.color * light.intensity * spec;
    //vec3 specular = vec3(0, 0, 0);
    return vec3(diffuse * GetColorMapColor(material.albedo) + specular * GetColorMapColor(material.specular));
}  

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
    vec3 tangentLightPos = TBN * light.position;
    vec3 lightDir = normalize(tangentLightPos - TangentFragPos);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.color * light.intensity * diff;

    // specular
    // vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir); 
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);     
    vec3 specular = light.color * light.intensity * 0.5 * spec;

    float distance = length(tangentLightPos - TangentFragPos);
    float attenuation = 1 / 
    ((light.quadratic * distance * distance )
    + (light.linear * distance)
    + (light.constant));

    // attenuation = attenuation > 0.3 ? 0.7 : 0.0;

    return vec3(diffuse * GetColorMapColor(material.albedo) + specular * GetColorMapColor(material.specular)) * attenuation;
}

vec3 CalcSpotLight(SpotLight spotLight, vec3 normal, vec3 viewDir)
{

    vec3 tangentLightPos = TBN * (spotLight.direction);
    vec3 lightDir = normalize(tangentLightPos - TangentFragPos);
    // vec3 lightDir = normalize(spotLight.position - FragPos);
    
    
    float theta = dot(lightDir, normalize(-spotLight.direction)); 
    // clamp((theta - currentLight.spotOuterCutoff) / epsilon, 0.0, 1.0)    
    float epsilon = spotLight.cutOff - spotLight.outerCutOff;
    float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
    if(theta / spotLight.outerCutOff > 1)
    {
        float diff = max(dot(normal, lightDir), 0.0);

        vec3 h = normalize(lightDir + viewDir);
        float spec = pow(max(dot(normal,h ), 0.0), material.shininess);

        float distance = length(tangentLightPos - TangentFragPos);
        float attenuation = 1.0 / (spotLight.constant 
                                    + spotLight.linear * distance 
                                    + spotLight.quadratic * (distance * distance));

        // attenuation = attenuation > 0.3 ? 0.7 : 0.0;    

        vec3 diffuse  = spotLight.color * spotLight.intensity * intensity * diff;
        vec3 specular = spotLight.color * spotLight.intensity * intensity * spec;

        return (diffuse * GetColorMapColor(material.albedo) + specular * GetColorMapColor(material.specular)) * attenuation; 
    }
    return vec3(0);
}

// Main

void main()
{
    TangentFragPos = TBN * FragPos;
    // TangentViewPos = TBN * viewPos;
    vec3 normal = GetColorMapColor(material.normalMap); 
    normal = normal * 2.0 - 1.0;   
    normal = normalize(TBN * normal); 
    vec3 viewDir = normalize(TangentViewPos - TangentFragPos);
    // vec3 viewDirBase = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0, 0.0, 0.0);

    //directional light
    for(int i = 0; i < lenghtDirLight; i++)
    {
        result += CalcDirLight(dirLights[i], normal, viewDir);
    }

    //point lights
    for(int i = 0; i < lenghtPointLight; i++)
    {
        result += CalcPointLight(pointLights[i], normal, viewDir);
    }

    //spot light
    for(int i = 0; i < lenghtSpotLight; i++)
    {
        result += CalcSpotLight(spotLights[i], normal, viewDir);
    }

    result += vec3(ambientColor) * GetColorMapColor(material.albedo);
    FragColor = vec4(result, 1.0);
    // FragColor = vec4(normal, 1);
}
