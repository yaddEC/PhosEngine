#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
uniform sampler2D albedoTexture;
// uniform vec3 viewPos;


uniform vec4 ambientColor;


// Structs

struct DirLight {
    vec3 direction;

    vec3 color;
    float intensity;
};  

uniform DirLight dirLights[];

struct PointLight {
    vec3 position;

    vec3 color;
    float intensity;

    float constant;
    float linear;
    float quadratic;
};

uniform PointLight pointLights[];

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

uniform SpotLight spotLights[];

// Fuctions

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.color * light.intensity * diff;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = /*material.specularColor **/ light.intensity/* * spec*/;
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
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = /*material.specularColor * */light.intensity/* * spec*/;

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

        vec3 diffuse  = spotLight.diffuse  * diff * intensity * attenuation;
        vec3 specular  = spotLight.specular * spec * intensity * attenuation;

        return (spotLight.ambient + diffuse + specular);  
    }
    return spotLight.ambient;
}

// Main

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec4 TextureColor = texture(texture1, TexCoord);

    vec3 result;
    bool lightActive = false;

    //directional light
    for(int i = 0; i < maxDirLights; i++)
    {
        if(dirLights[i].isActive == 1)
        {
            result = CalcDirLight(dirLights[i], norm, viewDir);
            lightActive = true;
        }
    }

    //point lights
    for(int i = 0; i < maxPointLights; i++)
    {
        if(pointLights[i].isActive == 1)
        {
            result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
            lightActive = true;
        }
    }

    //spot light
    for(int i = 0; i < maxSpotLights; i++)
    {
        if(spotLights[i].isActive == 1)
        {
            result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);
            lightActive = true;
        }
    }

    if(lightActive)
        FragColor = vec4(result, 1.0) * TextureColor;
    else
        FragColor = TextureColor;
}
