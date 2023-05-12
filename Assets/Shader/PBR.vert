#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in ivec4 aBoneWeightIndex;
layout (location = 6) in vec4 aBoneWeight;

out vec2 texCoord;
out vec3 FragPos;
out mat3 TBN;
out vec4 FragPosPoint[6];
out vec4 FragPosSpot[6];
out vec4 FragPosDir[3];

uniform mat4 mvp;
uniform mat4 model;

uniform mat4 spotLightSpace[6];
uniform mat4 pointLightSpace[6];
uniform mat4 dirLightSpace[3];

uniform mat4 skinMat[128];

uniform bool isSkinned = false;

void main()
{
    mat4 localPos = mat4(0);
    mat3 localNormal = mat3(0);



    if(isSkinned)
    {
        for(int i = 0; i < 4; i++)
        {
            if(aBoneWeightIndex[i] == -1) continue;
            localPos += skinMat[aBoneWeightIndex[i]] * aBoneWeight[i];
            localNormal += mat3(skinMat[aBoneWeightIndex[i]] * aBoneWeight[i]);
        }
    }
    else
    {
        localPos = mat4(1);
        localNormal = mat3(1);
    }
    
    vec4 resPos = localPos * vec4(aPos, 1.0);
    gl_Position =  mvp * resPos;
    texCoord = aTexCoord;
    FragPos = vec3(model * resPos);

    for(int i = 0; i < 6; i ++)
	{
		FragPosPoint[i] = pointLightSpace[i] * vec4(FragPos, 1.0);
		FragPosSpot[i] = spotLightSpace[i] * vec4(FragPos, 1.0);
        if (i < 3)
        {
		    FragPosDir[i] = dirLightSpace[i] * vec4(FragPos, 1.0);
        }
	}

    vec3 T = normalize(vec3(model * vec4(localNormal * aTangent, 0.0)));
    vec3 B = normalize(vec3(model * vec4(localNormal * aBitangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(localNormal * aNormal, 0.0)));
    TBN = mat3(T, B, N);
}