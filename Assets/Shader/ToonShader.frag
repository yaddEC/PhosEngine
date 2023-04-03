#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;


uniform vec3 viewPos;
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
};

uniform Material material;

#define ToonStep 0.4
#define ToonLightValue 0.7

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
    vec3 lightDir = normalize(-light.direction);

    float diff = dot(normal, lightDir) > ToonStep ? ToonLightValue : 0.0;
    vec3 diffuse = light.color * light.intensity * diff;

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) > ToonStep ? ToonLightValue : 0.0;
    vec3 specular = light.color * light.intensity * spec;
    //vec3 specular = vec3(0, 0, 0);
    return vec3(diffuse * GetColorMapColor(material.albedo) + specular * GetColorMapColor(material.specular));
}  

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - FragPos);

    float diff = dot(normal, lightDir) > ToonStep ? ToonLightValue : 0.0;
    vec3 diffuse = light.color * light.intensity * diff;

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) > ToonStep ? ToonLightValue : 0.0;
    vec3 specular = light.color * light.intensity * 0.5 * spec;

    float distance = length(light.position - FragPos);
    float attenuation = 1 / 
    ((light.quadratic * distance * distance )
    + (light.linear * distance)
    + (light.constant));

    attenuation = attenuation > 0.3 ? 0.7 : 0.0;

    return vec3(diffuse * GetColorMapColor(material.albedo) + specular * GetColorMapColor(material.specular)) * attenuation;
}

vec3 CalcSpotLight(SpotLight spotLight, vec3 normal, vec3 viewDir)
{
    
    vec3 lightDir = normalize(spotLight.position - FragPos);
    
    float theta = dot(lightDir, normalize(-spotLight.direction)); 
    // clamp((theta - currentLight.spotOuterCutoff) / epsilon, 0.0, 1.0)
    if(theta / spotLight.outerCutOff > 1)
    {
        float diff = dot(normal, lightDir) > ToonStep ? 1 : 0.0;

        vec3 h = (viewDir + lightDir)/length(viewDir + lightDir);
        float spec = pow(max(dot(h, normal), 0.0), material.shininess) > ToonStep ? 1 : 0.0;

        float distance = length(spotLight.position - FragPos);
        float attenuation = 1.0 / (spotLight.constant 
                                    + spotLight.linear * distance 
                                    + spotLight.quadratic * (distance * distance));

        attenuation = attenuation > 0.3 ? 0.7 : 0.0;

        vec3 diffuse  = spotLight.color * spotLight.intensity * diff;
        vec3 specular = spotLight.color * spotLight.intensity * spec;

        return (diffuse * GetColorMapColor(material.albedo) + specular * GetColorMapColor(material.specular)) * attenuation; 
    }
    return vec3(0);
}

// Main

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0, 0.0, 0.0);

    //directional light
    for(int i = 0; i < lenghtDirLight; i++)
    {
        result += CalcDirLight(dirLights[i], norm, viewDir);
    }

    //point lights
    for(int i = 0; i < lenghtPointLight; i++)
    {
        result += CalcPointLight(pointLights[i], norm, viewDir);
    }

    //spot light
    for(int i = 0; i < lenghtSpotLight; i++)
    {
        result += CalcSpotLight(spotLights[i], norm, viewDir);
    }

    result += vec3(ambientColor) * GetColorMapColor(material.albedo);
    FragColor = vec4(result, 1.0);
}
