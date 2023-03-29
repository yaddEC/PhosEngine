#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;


uniform sampler2D albedoTexture;
uniform vec3 viewPos;
uniform vec4 ambientColor;

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

// Fuctions

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.color * light.intensity * diff;

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);
    vec3 specular = light.color * light.intensity * spec;
    return vec3(diffuse + specular);
}  

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.color * light.intensity * diff;

    // vec3 h = (viewDir + lightDir)/length(viewDir + lightDir);
    // float spec = pow(max(dot(h, normal), 0.0), 32);

    // float distance = length(light.position - fragPos);
    // float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));



    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);
    vec3 specular = light.color * light.intensity * spec;

    float distance = length(light.position - FragPos);
    float attenuation = 1 / 
    ((light.quadratic * distance * distance )
    + (light.linear * distance)
    + (light.constant));

    return vec3(diffuse + specular) * attenuation;
}

vec3 CalcSpotLight(SpotLight spotLight, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    
    vec3 lightDir = normalize(spotLight.position - fragPos);
    
    float theta = dot(lightDir, normalize(-spotLight.direction)); 
    float epsilon = spotLight.cutOff - spotLight.outerCutOff;
    float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
    
    if(theta > spotLight.outerCutOff) 
    {   
        float diff = max(dot(normal, lightDir), 0.0);

        vec3 h = (viewDir + lightDir)/length(viewDir + lightDir);
        float spec = pow(max(dot(h, normal), 0.0), 32);

        float distance = length(spotLight.position - fragPos);
        float attenuation = 1.0 / (spotLight.constant 
                                    + spotLight.linear * distance 
                                    + spotLight.quadratic * (distance * distance));

        vec3 diffuse  = spotLight.color  * spotLight.intensity * intensity * diff;
        vec3 specular  = spotLight.color * spotLight.intensity * intensity * spec;

        return (diffuse + specular) * attenuation;  
    }
    return vec3(0);
}

// Main

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec4 TextureColor = texture(albedoTexture, TexCoord);

    vec3 result;

    //directional light
    for(int i = 0; i < lenghtDirLight; i++)
    {
        result += CalcDirLight(dirLights[i], norm, viewDir);
    }

    //point lights
    for(int i = 0; i < lenghtPointLight; i++)
    {
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    }

    //spot light
    for(int i = 0; i < lenghtSpotLight; i++)
    {
        result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);
    }

    result += vec3(ambientColor) * ambientColor.w;

    FragColor = vec4(result, 1.0) * TextureColor;
    // FragColor = TextureColor;
}
